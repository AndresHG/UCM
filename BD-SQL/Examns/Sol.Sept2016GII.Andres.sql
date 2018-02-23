--septiembre 2016 GII
--Andrés Herranz

--Autor (DNI, Nombre, Apellido, País)
--Firma (DNI, DOI)
--Artículo (DOI, Título, Revista)

--a
select nombre, apellido, count(*) as cuenta
from autor natural join firma natural join articulo
group by dni, nombre, apellido
union
select nombre, apellido, 0 as cuenta
from autor natural join firma
where doi not in(select distinct doi from articulo);

--b
select revista
from articulo
group by revista
having count(*) >= ALL (select count(*)
        from articulo
        group by revista);

--c
select revista
from articulo a
where a.revista like '%A%'and revista not in (select distinct revista
        from articulo natural join autor natural join firma
        where pais = 'España');
        
        
--Autor (DNI, Nombre, Apellido, País, NúmArtículos)
--Firma (DNI, DOI)
--Artículo (DOI, Título, ISSNRevista, NúmAutores)
--Revista (ISSN, Nombre)

--a
create or replace procedure p1 (p_nombre revista.nombre%type) is
v_revista revista%rowtype;
type v_autor is record(
    nombre autor.nombre%type,
    apellido autor.apellido%type);
cursor autores is
    select distinct au.nombre, au.apelldio
    from revista natural join articulo natural join firma natural join autor au
    where revista.nombre = p_nombre;
no_autores_exception exception;

begin
    select * into v_revista
    from revista
    where nombre = p_nombre;
    DBMs_OUTPUT.pu_line(v_revista.issn || revista.nombre);
    
    open autores;
    loop
        fetch autores into v_autor;
        exit when autores%notfound;
        DBMs_OUTPUT(v_autor.nombre || v_autor.apellido); 
    end loop;
    if autores%rowcount = 0 then
        raise no_autores_exception;
    end if;
    close autores;
    
    exception
        when no_autores_exception then DBMs_OUTPUT('No tiene autores');
        when no_data_found then DBMs_OUTPUT('No se ha encontrado la revista');
end;


--b
create or replace trigger tg1
after delete or update or insert on firma
for each row

begin
    if deleting then
        update articulo set numAutores = numautores -1
        where DOI = :OLD.DOI;
    elsif deleting then
        update articulo set numAutores = numautores +1
        where DOI = :OLD.DOI;
    else
        update articulo set numAutores = numautores -1
        where DOI = :OLD.DOI;
        update articulo set numAutores = numautores +1
        where DOI = :NEW.DOI;
    end if;
end;


