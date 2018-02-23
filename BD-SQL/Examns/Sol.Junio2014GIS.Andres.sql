--Junio 2014 GIS

--Pilotos(iniciales, Nombre, escuderia, pais)
--Circuitos(nombre, longitud, nVueltas)
--Parrilla(piloto, circuito, posicion_carrera)
--Tiempos(piloto, circuito, nVuelta, tiempo, paradaBoxes)

--a
select iniciales
from pilotos p1, pilotos p2
where p1.escuderia = p2.escuderia and p1.pais = p2.pais and p1.iniciales <> p2.iniciales;

select iniciales
from pilotos p1 join pilotos p2 on p1.escuderia = p2.escuderia and p1.pais = p2.pais
where p1.iniciales <> p2.iniciales;

--b
select ciercuito, max(tiempo)
from tiempos
group by circuito
order by 1;

--c
select nombre, longitud
from circuitos
where longitud >= ALL (select longitud
                                from circuitos);
                                
--d
select piloto, max(nVuelta), sum(tiempo)
from tiempos
where circuito = 'Monza'
group by piloto
order by 2, 3 asc;

--e
select escuderia, count(*)
from parrilla join iniciales on iniciales = piloto
where posicion_carrera in (1,2,3)
group by escuderia
having count(*) >= ALL (select count(*)
                from parrilla join iniciales on iniciales = piloto
                where posicion_carrera in (1,2,3)
                group by escuderia);

--f
select pi.nombre, ci.nombre, sum(ti.tiempo)
from (tiempos ti join pilotos pi on pi.inciiales = ti.piloto) join circuitos ci 
    on ci.nombre = ti.circuito
group by ti.piloto, ti.ciurcuito
having max(ti.nVuelta) = ci.nVueltas;

--g
select ci.circuito, avg((select count(*)
                    from tiempos
                    where circuito = ci.circuito and paradaBoxes = 1
                    group by piloto))
from circuitos ci;
                    