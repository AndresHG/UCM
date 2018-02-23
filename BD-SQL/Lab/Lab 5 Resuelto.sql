-- 1. Listado alfabético de las ciudades que tienen almacenes y no tienen departamentos. Usa una sintaxis con dos subconsultas. Esta pregunta la resolviste en la sesión 3 con JOINS y también se puede resolver con operadores de conjuntos. Vista: ciudades3 (ciudad)
  -- SOL: 5 TUPLAS
  
create or replace view ciudades3 (ciudad) as
SELECT DISTINCT city
  FROM locations
  where location_id in (select distinct location id from warehouses)
	and location_id not in (select distinct location id from departments)
  order by 1;
  
  select * from ciudades3;
  
  
-- 2. Número de personas, salario mínimo, medio y máximo de las personas que cobran menos que el salario medio de todos los puestos de trabajo. El salario medio de todos los puestos se calcula a través de la tabla employees. Vista: salario (n_personas, minimo, medio, maximo)
  -- SOL: 1 TUPLA
  
create or replace view salario (n_personas, minimo, medio, maximo) as
  SELECT  count(*), min(salary), avg(salary), max(salary)
  FROM employees
  where salary < ALL (select avg(salary) from employees group by job_id);
  
  select * from salario;
  

-- 3.  Mostrar el nombre de los productos de la categoría de peso 4 (weight_class=4) y su facturación. Ten en cuenta que en cada línea de pedido (order_item) hay un campo que indica la cantidad vendida (quantity). Ordéna el listado por ventas decrecientes. Vista: ventas4 (producto, facturación)
  -- SOL: 9 TUPLAS
  
  create or replace view ventas_4 (producto, facturación) as
  SELECT PRODUCT_NAME, SUM(UNIT_PRICE * QUANTITY)
  FROM PRODUCT_INFORMATION NATURAL JOIN ORDER_ITEMS 
  WHERE WEIGHT_CLASS=4
  GROUP BY PRODUCT_ID, PRODUCT_NAME
  ORDER BY 2 DESC;
  
  select * from ventas_4;
  
  
-- 4. Mostrar el nombre del producto y su facturación del producto con más facturación en la categoría de peso 4. PISTA: Para ello te resultará útil usar como subconsulta una consulta similar a la utilizada en el apartado anterior, pero simplemente con las facturación. Vista: top_ventas_4 (producto, facturación)
  -- SOL: 1 TUPLA
  
  -- Observad que la consulta madre y la consulta hija son prácticamente idénticas. 
  -- Observad también cómo obtener qué tupla tiene el mayor valor de una lista de tuplas (con el >=ALL) ya que se trata de una consulta bastante genérica.
  
  create or replace view top_ventas_4 (producto, facturación) as 
  SELECT PRODUCT_NAME, SUM(UNIT_PRICE * QUANTITY) 
  FROM PRODUCT_INFORMATION PI NATURAL JOIN ORDER_ITEMS 
  WHERE WEIGHT_CLASS=4
  GROUP BY PRODUCT_ID, PRODUCT_NAME
  HAVING SUM(UNIT_PRICE * QUANTITY) >=
			ALL (SELECT  SUM(UNIT_PRICE * QUANTITY)
					FROM PRODUCT_INFORMATION NATURAL JOIN ORDER_ITEMS 
					WHERE WEIGHT_CLASS=4
					GROUP BY PRODUCT_ID);
					
  select * from top_ventas_4;

-- 5. Mostrar el nombre y la facturación del producto con más facturación en cada una de las categorías de peso. Ordena el listado por categoría de peso. No puedes usar el operador de conjunto UNION para ello. Vista: top_ventas_categoria (categoria, producto, facturación)
    -- SOL: 5 TUPLAS

-- Observad que la consulta es prácticamente idéntica ala anterior, pero la consulta hija es correlacionada para filtrar por el weight_class que tenga la tupla de la consulta madre que estemos analizando en cada momento (además en la consulta madre no se filtra en el where para quedarnos con una weight class concreta porque las queremos todas).

	
  create or replace view top_ventas_categoria (categoria, producto, facturación) as
  SELECT WEIGHT_CLASS, PRODUCT_NAME, SUM(UNIT_PRICE * QUANTITY) 
  FROM PRODUCT_INFORMATION P NATURAL JOIN ORDER_ITEMS 
  GROUP BY PRODUCT_ID, PRODUCT_NAME, WEIGHT_CLASS
  HAVING SUM(UNIT_PRICE * QUANTITY) >=
			ALL (SELECT  SUM(UNIT_PRICE * QUANTITY)
					FROM PRODUCT_INFORMATION NATURAL JOIN ORDER_ITEMS 
					WHERE WEIGHT_CLASS=P.WEIGHT_CLASS
					GROUP BY PRODUCT_ID)
  ORDER BY 1;
  
  select * from top_ventas_categoria;

  
-- 6. De nuevo, haz el listado de las ciudades que tienen almacenes y no departamentos ordenado alfabéticamente. Usa una sintaxis con dos subconsultas, pero esta vez correlacionadas. Vista: ciudades4 (ciudad)
  -- SOL: 5 TUPLAS
  
  create or replace view ciudades4 (ciudad) as
  SELECT DISTINCT city
  FROM locations L
  where exists (select * from warehouses W where W.location_id=L.location_id)
	and not exists (select * from departments D where D.location_id=L.location_id)
  order by 1;
  
  select * from ciudades4; 

-- 7. Para los distintos modos de pedido (order_mode) obtener el gasto medio por cliente de los clientes que han hecho pedidos a través de dicho modo (es decir, en la media no hay que incluir a los clientes que no han hecho pedidos del modo para el que estemos calculando la media). Muéstra el listado por orden alfabético de order_mode. PISTA: calcula el gasto medio por modo de pedido que realiza cada uno de los clientes, y posteriormente calcula la media por modo. Vista: modos_pedido (modo, media_pedidos)
  -- SOL: dos tuplas
  
  -- En este caso se pretende que agreguéis doblemente. En una primera agregación por cliente y order_mode, para obtener lo que se gasta de media cada cliente para ambos order_mode.
  -- Una vez que tenemos una consulta con esa primera agregación la ponemos en el from y la usamos como tabla. Sobre dicha "tabla" ahora queremos agregar  por order_mode para obtener el gasto medio de los clientes en cada order_mode
		create or replace view modos_pedido (modo, media_pedidos) as
		select o.order_mode, AVG(o.gasto_m_cliente)
		from (select customer_id, order_mode, AVG(order_total) AS gasto_m_cliente
				from orders        
			  group by customer_id, order_mode) O
	    group by o.order_mode
		order by 1;

		select * from modos_pedido;
  
-- 8. Mostrar los empleados que ganen un 35% más del salario medio de su puesto. El listado debe incluir el puesto, el salario medio del puesto, el nombre y el apellido del empleado, así como su salario. El listado debe estar ordenado alfabéticamente por puesto y dentro de cada puesto por salario descendente. Vista: empleados_top (puesto,sal_medio, nombre, apellido, salario)


 -- En esta consulta el problema está enque hay que mostrar no solamente información de los empleados que cumplen la condición requerida, sino para cada uno de dichos empleados hay que incluir información agregada del puesto que tienen cada uno de estos empleados. En el "cada uno de estos" está la clave, ya que nos da la pista de que tenemos que correlacionar la consulta. Como el problema está en la información que se muestra la solución está en una subconsulta correlacionada en el SELECT.

create or replace view empleados_top (puesto,sal_medio, nombre, apellido, salario) as
select job_title, (select avg(salary) from employees where job_id= J.JOB_ID) AS AVG_SAL,  first_name, last_name, salary
from employees E join jobs J on J.JOB_ID = E.JOB_ID
where salary > 1.35*
                (select avg(salary) 
                  from employees where job_id= J.JOB_ID)
order by 1, 4 desc;   
    
select * from empleados_top;

-- 9. Listado alfabético de los departamentos de la empresa junto con su número de empleados, el salario máximo del departamento y el nombre de la persona que cobra dicho salario. Vista: departamentos_emp (departamento, empleados, salario_maximo, nombre_emp, apellido_emp)

 -- En esta consulta la dificultad consiste en concatenar en una misma tupla la información agregada de la tabla empleados con información sin agregar de la propia tabla empleados. Como no se puede hacer todo con una única tabla (porque o la agregas o no la agregas) necesitamos crear la tabla agregada e incorporarla en el from mediante una subconsulta select.

create or replace view departamentos_emp (departamento, empleados, salario_maximo, nombre_emp, apellido_emp) as 
  select E2.department_name, E2.N_EMP, E2.MAX_SAL, E1.first_name, E1.last_name
  FROM employees E1,  
		(SELECT department_id, department_name, count(employee_id) as N_EMP, max(salary) as MAX_SAL FROM employees JOIN departments using (department_id) GROUP BY department_id,department_name) E2
  WHERE E1.department_id = E2.department_id and E1.salary=E2.MAX_SAL
  
  
  ORDER BY 1;  

  
  select * from departamentos_emp;
  
  
