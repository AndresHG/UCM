--Cruceros(Referencia, Compañía, Precio)
--Puertos(Código, Nombre, País)
--Recorridos(Referencia, Código, NúmParada)

--b
select comapñia
from cruceros
where prcio > 1000
group by compañia
having count(*) >3;

--d
select referencia
from (cruceros natural join puertos) natural join recorridos
where nombre = 'Barcelona' and numParada = 0 and
    precio <= ALL  (select precio from (cruceros natural join puertos) natural join recorridos
                    where nombre = 'Barcelona' and numParada = 0);

--e
select referencia
from recorridos r join puertos p on r.codigo = p.codigo
where p.pais <> 'Grecia'
group by p.referencia
having count(*) = (select max(numParada) from recorridos
                    where referencia = p.referencia);
                    

--Guías(Nombre, Referencia)
--Grupos(IdReserva, Fecha, Nombre, Referencia)
--Recuento(Referencia,Visitas)

--a 
create or replace procedure p1(p_recorrido recuento.referencia%type, p_fecha date) as

v_ref guias.referencia%type;
v_nom guias.nombre%type;
no_guias_exception exception;
cursor cGuias is
    select nombre, fecha
    from grupos where nombre not in (select nombre from grupos where fecha = p_fecha) order by 1;

begin
    open cGuias;
    fetch cguias into v_nom;
    if cGuias%rowcount = 0 then
        raise no_guias_exception;
    end if;
    close cGuias;
    
    insert into grupos values(seq_grupos.NEXTVAL, p_fecha, v_nom, p_referencia);
    update recuento set visitas = visitas + 1 where referencia = p_referencia;
    DBMs_OUTPUT.put_line('Grupo añadido correctamente el dia' || to_char(p_date, 'dd/mm/yy'));
    
    exception
        when no_guias_exception then DBMs_OUTPUT.put_line('No hay guias libres ese día');
end;

--b
create or replace trigger tg1
before delete on Grupos
for each row

begin
    update recuento set visitas = visitas +1
    where referencia = :OLD.referencia;
end;









