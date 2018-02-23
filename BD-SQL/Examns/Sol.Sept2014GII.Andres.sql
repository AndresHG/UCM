--Pacientes(Historial, SS, Nombre, Domicilio, Teléfono)
--Ingresos(ID, Historial, CódMédico, Fecha, Diagnóstico)
--Médicos(CódMédico, Nombre, Especialidad)


--b
select count(*)
from medicos
where especialidad like 'Ped%';

--c
select distinct historial
from infresos natural join medicos
where especialidad <> 'Ped%';

--d
select codMedico, nombre, count(*)
from medicos natural join ingresos
group by codMedico, nombre
having count(*) >= ALL (select count(*) from medicos natural join ingresos
                        group by codMedico, nombre)
order by 1,2;


--Empleados( DNI, Nombre, codDept, Salario)
--RegistroCambios(IdCambio,Usuario, Fecha, salAnterior, salActual)

--e
create or replace trigger tg1
after update of salario on empleados
for each row

--f
begin
    insert into registroCambios
    values(SEQCambios.nextval, :OLD.dni, sysdate,  :OLd.salario, :new.salario);
end;
/

--g
create or replace procedure p1 is

cursor cr1 is
select * from empleados
order by codDpt;
registro empleados%rowtype;

begin
    loop
        fetch cr1 into registro;
        exit when registro%notfound;
        if registro.salario > (select avg(salary) from empleados where codDpt = registro.codDpt) then
            DBMs_OUTPUT.put(registro.DNI || registro.Nombre || registro.codDept || registro.salario);
        end if;
    end loop;
end;
--Faltaria el total de salario por departamento


create or replace procedure p1 is

cursor cr1 is
select nombre, codDept, salario, (select avg(salary) from empleados where codDpt = e.codDpt) as media
from empleados e
where e.salario > (select avg(salary) from empleados where codDpt = e.codDpt)
order by codDpt;
registro empleados%rowtype;

begin
    loop
        fetch cr1 into registro;
        exit when registro%notfound;
        DBMs_OUTPUT.put(registro.media || registro.Nombre || registro.codDept || registro.salario);
    end loop;
end;
--Aqui mostraría en cada tupla la media del departamente, el nombre del individuo, codigo de departamento y su salario

