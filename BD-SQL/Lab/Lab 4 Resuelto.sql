
-- 1.  Listado alfabético de todos los status de producto (product_status) junto con el número de productos que hay de cada uno de ellos. Vista: status(estado, n_productos)
  -- SOL: 4 TUPLAS
  -- sol 1:
     create or replace view status(estado, n_productos) as
     select  PRODUCT_STATUS, count(*)
     from PRODUCT_INFORMATION      
     group by PRODUCT_STATUS
     order by 1;
	 
	 select * from status;

-- 2. Listado alfabético con los puestos de trabajo en los que hay empleados que cobran el salario mínimo establecido para dicho puesto.  Vista: salario_minimo (puesto, n_empleados)
  -- SOL: 2 TUPLAS	 
	create or replace view salario_minimo (puesto, n_empleados)  as
	 SELECT JOB_TITLE, COUNT(*)
	 FROM JOBS NATURAL JOIN EMPLOYEES
	 WHERE MIN_SALARY=SALARY
	 GROUP BY JOB_ID, JOB_TITLE
	 order by 1;	 
	 
	 select * from salario_minimo;
	 
-- 3. Listado alfabético de todos los productos con status "orderable" que se encuentren en 10 almacenes así como su cantidad total disponible (es decir, en todos los almacenes).  Vista: orderable(producto, cantidad)
  -- SOL: 1 TUPLA
  -- OJO: Si agregas por product_id no hay ningún producto que esté en 10 almacenes!!! product_name no es clave candidata.
	 create or replace view orderable(producto, cantidad) as
	 select  product_name, sum(quantity_on_hand)
     from PRODUCT_INFORMATION natural join inventories
     where PRODUCT_STATUS like 'orderable'
     group by product_name
     having count(*)=10
     order by 1;
	 
	 select * from salario_minimo;

-- 4.	Listado alfabético de los almacenes de Estados Unidos que tienen menos de 50 productos diferentes. Incluye el el número de productos diferentes que hay en cada almacen. Vista: almacen_usa(almacen, n_productos)
  -- SOL: 2 TUPLAS
  -- sol 1:
  create or replace view almacen_usa(almacen, n_productos) as
	select warehouse_name, count(*)
		from ((inventories natural  join warehouses) natural join locations) natural join countries
    where country_name like 'United States%'
	group by warehouse_name
    having count(*)<50
	ORDER BY 1;
	
	select * from almacen_usa;

-- 5. Ranking anonimizado (sin nombre y apellidos) de los clientes que tienen límite de crédito igual a 100 y que indique únicamente su territorio (NLS_territory) el número de pedidos que ha realizado y el total de dinero gastado en ellos ordenado de manera descendente por el dinero gastado. Ojo porque el listado debe incluir a aquellos clientes que no han hecho pedidos y reflejar un cero si no se han gastado dinero. Vista: cli_anonim (territorio, n_pedidos, total_gastado) 	
-- SOL: 11 tuplas
create or replace view cli_anonim (territorio, n_pedidos, total_gastado)  as
	select NLS_territory, count(order_total), sum(COALESCE(order_total,0))
		from customers left join orders using (customer_id)
        where credit_limit <=100
	    group by customer_id, NLS_territory
	    ORDER BY 3 desc;
  
	select * from cli_anonim;
	
	-- En lugar de coalesce sería más adecuado poner NVL(order_total, 0) pero no la hemos visto en los apuntes

-- 6. Listado de productos de categoría de peso 4 (weight_class) que se han vendido con precio diferente en los pedidos (unit_price), indicando el número de veces que se ha vendido dicho artículo, su precio mínimo, su precio medio y su precio máximo. Vista: prod_precio_venta (producto, ventas, precio_min, precio_med, precio_max) 
  -- SOL: 4 tuplas
     create or replace view prod_precio_venta (producto, ventas, precio_min, precio_med, precio_max)  as
	 SELECT product_name, COUNT(*), MIN(unit_price), AVG(unit_price), MAX(unit_price)
	 FROM order_items NATURAL JOIN product_information
     WHERE weight_class=4
	 GROUP BY product_id, product_name
     HAVING MAX(UNIT_PRICE)<>MIN(UNIT_PRICE)
     ORDER BY 1;
	 
	 select * from prod_precio_venta;
  
-- 7. Muestra el nombre, apellido, el puesto y el salario del empleado que menos dinero cobra en la compañía. Vista: empleado_sal_minimo (nombre, apellido, puesto, salario)
  -- SOL: 1 Fila
  create or replace view empleado_sal_minimo (nombre, apellido, puesto, salario) as
  select first_name,  last_name, job_title, salary
  from employees natural join jobs
  WHERE salary =
	(SELECT min(salary) from employees);
  
  select * from empleado_sal_minimo;
  
-- 8.	Muestra el nombre y apellido de los clientes que no han hecho ningún pedido. Hazlo usando una subconsulta aunque también lo podrías hacer con reuniones externas. Ordénalo por apellido y nombre. Vista: clientes_sin_pedido(apellido,nombre)
  -- SOL: 103 PRODUCTOS
  create or replace view  clientes_sin_pedido(apellido,nombre) as
  select  cust_last_name, cust_first_name
  from customers
  WHERE customer_id NOT in (SELECT distinct customer_id FROM ORDERs)
  order by 1,2;
  
  select * from clientes_sin_pedido;
                  
	
-- 9. Listado alfabético de los puestos de la compañía cuyo salario medio es superior al salario medio de los empleados de la compañía. El listado debe incluir también el número de empleados que ejercen cada puesto y solamente aquellos puestos que sean ejercidos por más de un empleado. Vista: puestos_sobre_media(puesto,salario_medio, n_empleados)
-- SOL: 5 filas
create or replace view  puestos_sobre_media(puesto,salario_medio, n_empleados) as
select jobs.JOB_TITLE, avg(salary) as SALARIO_MEDIO, count(*) as NUMERO_EMPLEADOS 
    from employees natural inner join jobs
  group by job_id, job_title
  having count(*)>1 AND avg(salary) > 
                (select avg(salary) from employees)  
  order by 1; 	
   			
			
  select * from puestos_sobre_media;
    