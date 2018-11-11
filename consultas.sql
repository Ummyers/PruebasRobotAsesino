/*a. Encontrar el nombre y la ciudad de todos los empleados que trabajan en PEMEX.*/
SELECT a.nombre,a.ciudad
FROM Empleado a JOIN Trabajar b ON a.curp=b.curp JOIN Empresa c ON b.rfc=c.rfc
WHERE c.razon_social = 'PEMEX';

/* b. Encontrar todos los empleados que viven en la misma ciudad en la que trabajan.*/
SELECT a.nombre,a.paterno,a.materno,a.ciudad
FROM Empleado a JOIN Trabajar b ON a.curp=b.curp JOIN Empresa c on b.rfc=c.rfc
WHERE a.ciudad= c.ciudad;

/*c. Calcular el salario de todos los directores.*/
SELECT nombre,paterno,materno,salario
FROM Empleado e JOIN Trabajar t on e.curp=t.curp JOIN Dirigir d ON t.curp=d.curp
ORDER BY salario;

/*d. Obtener la información de los directores y empresas que comenzaron a dirigir
	 dicha empresa en el primer y tercer semestre del año que tú elijas.*/
SELECT d.* , e.*
FROM Dirigir d JOIN Empleado e ON d.curp  = e.curp
	JOIN Empresa m ON m.rfc = d.rfc
WHERE (extract (month from d.fecha_inicio) <= 4 OR extract(month from d.fecha_inicio) >= 9) 
		AND extract(year from d.fecha_inicio) = 1996;

/*e. Encontrar a todos los empleados que viven en la misma ciudad y en la misma 
	 calle que su supervisor.*/
select e.nombre,e.paterno,e.materno,e.curp,e.f_nac,e.calle,e.num,e.ciudad,e.cp
from Empleado e join Supervisar s on s.curp_jefe = e.curp join Empleado e2 on s.curp_supervisado=e2.curp
where e.calle=e2.calle and e.ciudad=e2.ciudad;

/*f. Obtener una lista de cada compañía y el salario promedio que paga.*/
SELECT e.rfc, AVG(t.salario) "salario_promedio"
FROM Empresa e JOIN Trabajar t ON e.rfc = t.rfc
GROUP BY e.rfc;

/*g. Empleados que colaboran en proyectos que controlan empresas para las que no trabajan.*/
(SELECT e.curp, m.rfc
FROM (((Empleado e JOIN Colaborar c ON e.curp = c.curp)
	JOIN Controlar p ON p.numProy = c.numProy)
	JOIN Empresa m ON m.rfc = p.rfc))
MINUS
(SELECT curp, rfc
FROM Trabajar);

/*h. Encontrar el total de salarios pagados por cada compañía.*/
SELECT rfc, COUNT(salario) "Total salarios"
FROM Trabajar
GROUP BY rfc;

/*i. Encontrar información de los empleados y número de horas que dedican a los proyectos, para
	 aquellos empleados que colaboran en al menos dos proyectos y en donde el número de horas que
	 dediquen a algún proyecto sea mayor a 20.*/
SELECT *
FROM Empleado e JOIN 
    (SELECT curp, COUNT(numProy) "Num. Proyectos", SUM(numHoras) "Num. Total Horas"
    FROM Colaborar
    WHERE numHoras>20
    GROUP BY curp) g ON e.curp=g.curp;

/*j. Encontrar la cantidad de empleados de cada compañía. */
SELECT rfc, COUNT(curp) Cantidad_Empleados
FROM Trabajar t
GROUP BY rfc;

/*k. Encontrar el nombre del empleado que gana más dinero de cada compañía.*/
SELECT n.nombre, n.rfc
FROM (SELECT t.rfc, max(salario) salario
	FROM Trabajar t JOIN Empresa e ON t.rfc=e.rfc
	GROUP BY t.rfc) m 
	JOIN 
	(SELECT rfc, nombre, salario
	FROM Empleado e JOIN Trabajar t ON e.curp=t.curp) n 
	ON m.rfc=n.rfc AND m.salario=n.salario;

/*l. Obtener una lista de los empleados que ganan más del salario promedio que pagan las compañías.*/
SELECT e.curp,e.nombre,e.paterno,e.materno
FROM Trabajar t JOIN Empleado e ON t.curp=e.curp
WHERE salario > (SELECT AVG(p."salario_promedio") "salario_promedio"
				FROM (SELECT e.rfc, AVG(t.salario) "salario_promedio"
                FROM Empresa e JOIN Trabajar t ON e.rfc = t.rfc
                GROUP BY e.rfc) p);

/*m. Encontrar la compañía que tiene menos empleados y listar toda la información de los mismos.*/
SELECT a.*
FROM (SELECT rfc, COUNT(curp) "num_empleados" FROM Trabajar GROUP BY rfc) e 
	JOIN 
	(SELECT MIN(n."num_empleados") "min_num_empleados"
	FROM (SELECT rfc, COUNT(curp) "num_empleados"
		FROM Trabajar
		GROUP BY rfc) n) m 
	ON e."num_empleados" = m."min_num_empleados"
	INNER JOIN Trabajar t ON t.rfc = e.rfc
	INNER JOIN Empleado a ON a.curp = t.curp;

/*n.  Información de los proyectos en los que colaboran los empleados que son directores.*/
SELECT p.numProy,p.nombre,p.fecha_inicio,p.fecha_fin
FROM Proyecto p JOIN Colaborar c ON p.numProy=c.numProy JOIN Empleado a ON a.curp=c.curp JOIN Dirigir b ON a.curp=b.curp;

/*o. Encontrar la compañía que tiene empleados en cada una de las ciudades que hayas definido.*/
/*--- No se resolvió ---*/

/*p. Empleados que dejaron de colaborar en proyectos, antes de la fecha de finalización de los mismos.*/
SELECT e.*
FROM Empleado e JOIN Colaborar c ON e.curp = c.curp
	JOIN Proyecto p ON p.numProy = c.numProy
WHERE c.fecha_fin < p.fecha_fin;


/*q. Información de los empleados que no colaboran en ningún proyecto.*/
SELECT m.*
FROM (SELECT curp
	FROM Empleado
	MINUS
	SELECT curp
	FROM Colaborar) e JOIN Empleado m ON e.curp = m.curp;

/*r. Encontrar la información de las compañías que tienen al menos dos empleados en la misma
	 ciudad en que tienen sus instalaciones. */
SELECT *
FROM (SELECT m.rfc, COUNT(e.curp) "num_empleados_misma_ciudad"
	  FROM Empleado e JOIN Trabajar t ON e.curp = t.curp
	  JOIN Empresa m ON m.rfc = t.rfc
	  WHERE e.ciudad = m.ciudad
	  GROUP BY m.rfc) d JOIN Empresa e ON e.rfc = d.rfc
WHERE "num_empleados_misma_ciudad" >= 2;

/*s.  Proyecto que más empleados requiere (o requirió) y el número de horas que éstos le dedicaron.*/
/*--- No se resolvió ---*/

/*t. Empleados que comenzaron a colaborar en proyectos en la misma fecha de su cumpleaños.*/
SELECT e.*
FROM Empleado e JOIN Colaborar c ON e.curp = c.curp
WHERE extract(day FROM e.f_nac) = extract(day FROM c.fecha_inicio)
	AND extract(month FROM e.f_nac) = extract(month FROM c.fecha_inicio);

/*u. Obtener una lista del número de empleados que supervisa cada supervisor.*/
SELECT curp_jefe, COUNT(curp_supervisado) "Num_Supervisados"
FROM Supervisar
GROUP BY curp_jefe;

/*v. Obtener una lista de los directores de más de 50 años.*/
SELECT e.*
FROM Empleado e JOIN Trabajar t ON e.curp=t.curp JOIN Dirigir d ON t.curp=d.curp
WHERE extract(year FROM e.f_nac) <= 1968;

/*w. Obtener una lista de los empleados cuyo apellido paterno comience con las letras A, D, G, J, L, P ó R.*/
SELECT *
FROM Empleado a
WHERE regexp_like(lower(paterno),'^a.*') OR regexp_like(lower(paterno),'^d.*') OR regexp_like(lower(paterno),'^g.*')
	  OR regexp_like(lower(paterno),'^j.*') OR regexp_like(lower(paterno),'^l.*') OR regexp_like(lower(paterno),'^p.*')
	  OR regexp_like(lower(paterno),'^r.*')
ORDER BY paterno;

/*x. Número de empleados que colaboran en los proyectos que controla cada empresa
	 para aquellos proyectos que hayan iniciado en diciembre. */
SELECT COUNT(curp) "num_empleados"
FROM Proyecto p JOIN Colaborar c ON p.numProy = c.numProy
WHERE extract(month from p.fecha_inicio) = 12;

/*y. Crea una vista con la información de los empleados y compañías en que trabajan,
	 de aquellos empleados que lo hagan en al menos tres compañías diferentes. */
/*--- No se resolvió ---*/