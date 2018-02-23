--1
select pi.product_name
from product_information pi
where pi.product_name
like '%HD%' 
group by pi.product_name;

--2
select order_id, product_name
from order_items
join product_information 
using(product_id)
where product_status = 'obsolete'

--3
select product_name, translated_name
from product_information natural join product_descriptions
where product_name <> translated_name

--4
select country_id, state_province, location_id,department_name
from (locations  join countries using(country_id))
left outer join departments using (location_id)
order by location_id;

--5
select country_id, state_province,location_id, d.department_name,w.warehouse_name
from ((locations natural inner join warehouses w )natural join departments d)
where d.department_name is not null or w.warehouse_id is not null;

--6
select country_id, city ,location_id, department_name, warehouse_name
from(warehouses natural RIGHT outer join locations)
natural inner join (departments natural RIGHT outer join locations)
order by country_id desc, city

--7
select distinct first_name, last_name, cust_first_name, cust_last_name
from (orders natural inner join customers) join employees
on customers.account_mgr_id = employees.employee_id

--8
select category_id, count(*)
from product_information
where product_status = 'obsolete'
GROUP by category_id
having count(*) > 4;

--9
select oi.order_id, pi.product_name
from (order_items oi join product_information pi using (product_id))
where pi.product_status='obsolete'
order by oi.order_id


--10

select order_id, count(*)
from (order_items join product_information using(product_id))
where product_status = 'obsolete'
group by order_id
having count (*) > 2

--11

select product_name,count(*), sum(quantity)
from (product_information  natural inner join order_items) natural inner join orders
where order_date > '01/01/00' 
AND order_date < '01/01/01'
GROUP by product_name
order by sum(quantity) desc;

--12
select job_title, min_salary
from jobs
WHERE min_salary  > (select AVG(salary) from employees)
order by min_salary

--13
select product_id, product_name, min_price
from product_information
where product_id not in (select distinct product_id from order_items)

--14


