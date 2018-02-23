--Contratos(Referencia, Empresa, FechaInicio)
--Contiene(Referencia, Origen, Destino, Fecha, Vehículo, coste)

--a
select distinct vehiculo
from contiene natural join contratos
where empresa like 'A%'
order by 1;

--b
select empresa
from contratos
where fechaInicio > '31.12.2013' and fechaInicio < '1-1-2015'
group by empresa
having count(*) > 5;

--c
select vehiculo
from contiene
where origen = madrid and destino = barcelona
group by origen, destino
having min(coste) = coste;

--d
delete from contratos
where referencia not in (select referencia from contiene);


--Contratos(Referencia, Empresa, Fecha, NumTrayectos)
--Contiene(Referencia, Origen, Destino, Vehículo)

-- e
create or replace trigger tg1
before delete on contratos
for each row

begin
    delete from contiene c
    where c.referencia = :OLD.referencia;
end;
/

--f
create or replace procedure p1 (in p_referencia CHAR(6)) is
contador number(5);
no_excep exception;

begin
    select count(*) into contador
    from contiene
    where referencia = p_referencia;
    
    update contratos
    set numTrayectos = contador
    where referencia = p_referencia;
    
    if contador = 0 then
        raise no_excep
    else
        DBMs_OUTPUT.put('El contrato' || p_referencia || 'tiene' || contador || 'trayectos');
    end if;
    
    exception
        when no_excep DBMs_OUTPUT.put('No tiene trayectos');
end;

--g
create or replace trigger tg2
before insert or delete on contiene
for each row

begin
    if DELETING THEN
        update contratos set numTrayectos := numTrayectos -1
        where referencia = :OLD.referencia;
    else
        update contratos set numTrayectos := numTrayectos +1
        where referencia = :NEW.referencia;
    END IF;
end;
/







        
