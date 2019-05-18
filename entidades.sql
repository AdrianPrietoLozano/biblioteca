
/*
*
*
IGNORAR ESTO
*
*
INSERT INTO cliente(nombre, telefono, departamento, carrera, grado, sexo, tipo)
	VALUES('Adrian', '12345', 'alguno', 'inni', null, 'H', 'E');


INSERT INTO prestamo(codigo_libro, codigo_cliente, codigo_empleado, fecha_prestamo)
	VALUES(1, 2, 3, "")


SELECT usuario.tipo AS tipo, count(prestamo.codigo) AS num_prestamos
	FROM usuario, prestamo WHERE usuario.codigo=1
		AND prestamo.codigo_cliente=1 GROUP BY usuario.tipo


SELECT codigo, nombre, nombre_usuario, PGP_SYM_DECRYPT(contrasenia, 'equipo7'),
edad, salario, sexo FROM empleado;
*/


CREATE TABLE libro
(
	codigo SERIAL NOT NULL,
	isbn VARCHAR(30) NOT NULL,
	titulo VARCHAR(100) NOT NULL,
	autor VARCHAR(100),
	editorial VARCHAR(100),
	ejemplar INT NOT NULL,
	anio_publicacion INT,
	PRIMARY KEY(codigo)
);


CREATE TABLE cliente
(
	codigo SERIAL NOT NULL,
	nombre VARCHAR(100) NOT NULL,
	telefono VARCHAR(25),
	departamento VARCHAR(100),
	carrera VARCHAR(50),
	grado INT,
	sexo CHAR CHECK(sexo IN ('H', 'M')),
	tipo CHAR CHECK(tipo IN ('E', 'P', 'A')) DEFAULT 'E',
	PRIMARY KEY(codigo)
);


CREATE TABLE empleado
(
	codigo SERIAL NOT NULL,
	nombre VARCHAR(100) NOT NULL,
	nombre_usuario VARCHAR(30) NOT NULL,
	contrasenia BYTEA NOT NULL,
	edad INT,
	salario DECIMAL,
	sexo CHAR CHECK(sexo IN ('H', 'M')),
	es_administrador BOOLEAN NOT NULL DEFAULT FALSE,
	PRIMARY KEY(codigo),
	UNIQUE(nombre_usuario)
);

CREATE TABLE prestamo
(
	codigo SERIAL NOT NULL,
	codigo_libro INT NOT NULL,
	codigo_cliente INT NOT NULL,
	codigo_empleado INT NOT NULL,
	fecha_prestamo TIMESTAMP NOT NULL,
	fecha_entrega TIMESTAMP NOT NULL,
	PRIMARY KEY(codigo),
	UNIQUE(codigo_libro),
	FOREIGN KEY(codigo_libro) REFERENCES libro(codigo),
	FOREIGN KEY(codigo_cliente) REFERENCES cliente(codigo),
	FOREIGN key(codigo_empleado) REFERENCES empleado(codigo)
);

INSERT INTO empleado(nombre, nombre_usuario, contrasenia, edad, salario,
	sexo, es_administrador)
	VALUES('equipo 7', 'equipo 7', PGP_SYM_ENCRYPT('12345', 'equipo7'),
    	20, 1000, 'H', TRUE);





"SELECT codigo, nombre, telefono, departamento, carrera, grado, sexo, tipo "\
"FROM (SELECT codigo, nombre, telefono, departamento, carrera, grado, "\
	"CASE WHEN sexo='H' THEN 'Hombre' "\
     	"WHEN sexo='M' THEN 'Mujer' "\
	"END AS sexo, "\
	"CASE WHEN tipo='E' THEN 'Estudiante' "\
     	"WHEN tipo='P' THEN 'Profesor' "\
     	"WHEN tipo='A' THEN 'Ambos' "\
	"END AS tipo FROM cliente) AS temporal "\




SELECT * , EXTRACT( days from to_timestamp(CAST(fecha_entrega as varchar), 'yyyy-mm-dd') - to_timestamp(CAST(now() AS VARCHAR), 'yyyy-mm-dd') )
FROM prestamo;


SELECT * , EXTRACT( days from fecha_entrega - now() )
FROM prestamo;


 update prestamo set fecha_entrega= timestamp '2019-05-12 21:54:23';



INSERT INTO prestamo(codigo_libro, codigo_cliente, codigo_empleado, fecha_prestamo, fecha_entrega)
VALUES (5, 1, 1, timestamp '2019-05-11 21:34:23', timestamp '2019-05-11 21:34:23');


//----------------------------------------------------------------------------


SELECT codigo, titulo, nombre_cliente, nombre_empleado,
	to_char(fecha_prestamo, 'dd-mm-yyyy,  hh24:mi AM'),
	to_char(fecha_entrega, 'dd-mm-yyyy,  hh24:mi AM'),
	CASE WHEN ejemplar = 1 THEN CONCAT(TRUNC(retraso / 3600), ' horas')
		 WHEN ejemplar <> 1 THEN CONCAT(TRUNC(retraso / 86400), ' días')
	END AS retraso,
	CASE WHEN ejemplar = 1 THEN CONCAT('$', TRUNC(retraso / 3600) * 1)
		 WHEN ejemplar <> 1 THEN CONCAT('$', TRUNC(retraso / 86400) * 5)
	END AS penalizacion

	FROM

(SELECT prestamo.codigo, titulo, cliente.nombre AS nombre_cliente, empleado.nombre AS nombre_empleado,
		fecha_prestamo, fecha_entrega, ejemplar,
	CASE 
		WHEN ejemplar = 1 AND EXTRACT( EPOCH from now() - fecha_entrega ) <= 0 THEN 0
		WHEN ejemplar = 1 AND EXTRACT( EPOCH from now() - fecha_entrega ) > 0
			THEN EXTRACT( EPOCH from now() - fecha_entrega )
		WHEN ejemplar <> 1 AND EXTRACT( EPOCH from now() - (fecha_entrega - interval '24 hours') ) <= 0 THEN 0
		WHEN ejemplar <> 1 AND EXTRACT( EPOCH from now() - (fecha_entrega - interval '24 hours') ) > 0
			THEN EXTRACT( EPOCH from now() - (fecha_entrega - interval '24 hours') )
	END AS retraso	
    FROM prestamo LEFT JOIN libro ON libro.codigo=codigo_libro
    LEFT JOIN cliente ON cliente.codigo=codigo_cliente
    LEFT JOIN empleado ON empleado.codigo=codigo_empleado) AS temporal;


"CASE "\
	"WHEN ejemplar = 1 AND EXTRACT( EPOCH from now() - fecha_entrega ) <= 0 THEN 0 "\
	"WHEN ejemplar = 1 AND EXTRACT( EPOCH from now() - fecha_entrega ) > 0 "\
		"THEN EXTRACT( EPOCH from now() - fecha_entrega ) "\
	"WHEN ejemplar <> 1 AND EXTRACT( EPOCH from now() - (fecha_entrega - interval '24 hours') ) <= 0 THEN 0 "\
	"WHEN ejemplar <> 1 AND EXTRACT( EPOCH from now() - (fecha_entrega - interval '24 hours') ) > 0 "\
		"THEN EXTRACT( EPOCH from now() - (fecha_entrega - interval '24 hours') ) "\
"END AS retraso	 "\

//----------------------------------------------------------------------------

"SELECT L.titulo, L.ejemplar, C.nombre, CASE WHEN C.tipo='E' THEN 'Estudiante' "\
     	"WHEN C.tipo='P' THEN 'Profesor' "\
     	"WHEN C.tipo='A' THEN 'Estudiante y profesor' END AS tipo, fecha_entrega "\
"FROM prestamo AS P LEFT JOIN libro AS L ON L.codigo=codigo_libro "\
			"LEFT JOIN cliente AS C ON C.codigo=codigo_cliente "\
"WHERE P.codigo=?";



UPDATE prestamo SET fecha_entrega=timestamp '01-03-2019 17:00:00' WHERE codigo=26;
UPDATE prestamo SET fecha_entrega=timestamp '11-04-2019 20:00:00' WHERE codigo=27;
UPDATE prestamo SET fecha_entrega=timestamp '30-05-2019 20:30:00' WHERE codigo=28;
UPDATE prestamo SET fecha_entrega=timestamp '01-01-2019 17:00:00' WHERE codigo=29;
UPDATE prestamo SET fecha_entrega=timestamp '06-06-2017 17:00:00' WHERE codigo=30;
UPDATE prestamo SET fecha_entrega=timestamp '12-12-2018 17:00:00' WHERE codigo=31;
UPDATE prestamo SET fecha_entrega=timestamp '12-12-2010 17:00:00' WHERE codigo=54;


INSERT INTO prestamo(codigo_libro, codigo_cliente, codigo_empleado, fecha_prestamo, fecha_entrega)
VALUES (7, 1, 1, timestamp '2019-05-11 12:34:23', timestamp '2019-05-11 17:00:00');



INSERT INTO libro (isbn, titulo, autor, editorial, ejemplar, anio_publicacion) VALUES
	('978-84-7829-085', 'Fundamentos de Sistemas de Bases de Datos', 'Ramez Elmasri, Shamkant B. Navathe', 'Pearson educación', 1, 2007),
	('978-84-7829-085', 'Fundamentos de Sistemas de Bases de Datos', 'Ramez Elmasri, Shamkant B. Navathe', 'Pearson educación', 2, 2007),
	('978-84-7829-085', 'Fundamentos de Sistemas de Bases de Datos', 'Ramez Elmasri, Shamkant B. Navathe', 'Pearson educación', 3, 2007),
	('978-84-7829-085', 'Fundamentos de Sistemas de Bases de Datos', 'Ramez Elmasri, Shamkant B. Navathe', 'Pearson educación', 4, 2007),
	('978-84-7829-085', 'Fundamentos de Sistemas de Bases de Datos', 'Ramez Elmasri, Shamkant B. Navathe', 'Pearson educación', 5, 2007),
	('978-84-7829-085', 'Fundamentos de Sistemas de Bases de Datos', 'Ramez Elmasri, Shamkant B. Navathe', 'Pearson educación', 6, 2007),
	('978-84-7829-085', 'Fundamentos de Sistemas de Bases de Datos', 'Ramez Elmasri, Shamkant B. Navathe', 'Pearson educación', 7, 2007),
	('978-84-7829-085', 'Fundamentos de Sistemas de Bases de Datos', 'Ramez Elmasri, Shamkant B. Navathe', 'Pearson educación', 8, 2007),
	('978-84-7829-085', 'Fundamentos de Sistemas de Bases de Datos', 'Ramez Elmasri, Shamkant B. Navathe', 'Pearson educación', 9, 2007),
	('978-84-7829-085', 'Fundamentos de Sistemas de Bases de Datos', 'Ramez Elmasri, Shamkant B. Navathe', 'Pearson educación', 10, 2007);
	

INSERT INTO libro (isbn, titulo, autor, editorial, ejemplar, anio_publicacion) VALUES
	('9786073157063', 'It', 'Stephen King', 'Viking Press', 1, 1986),
	('9786073157063', 'It', 'Stephen King', 'Viking Press', 2, 1986),
	('9786073157063', 'It', 'Stephen King', 'Viking Press', 3, 1986),
	('9786073157063', 'It', 'Stephen King', 'Viking Press', 4, 1986),
	('9786073157063', 'It', 'Stephen King', 'Viking Press', 5, 1986),
	('9786073157063', 'It', 'Stephen King', 'Viking Press', 6, 1986),
	('9786073157063', 'It', 'Stephen King', 'Viking Press', 7, 1986),
	('9786073157063', 'It', 'Stephen King', 'Viking Press', 8, 1986),
	('9786073157063', 'It', 'Stephen King', 'Viking Press', 9, 1986),
	('9786073157063', 'It', 'Stephen King', 'Viking Press', 10, 1986);


INSERT INTO libro (isbn, titulo, autor, editorial, ejemplar, anio_publicacion) VALUES
	('978-607-481-826-0', 'Precálculo Matemáticas para el cálculo', 'James Stewart, Lothar Redlin, Saleem Watson', 'CENAGAGE Learning', 1, 2012),
	('978-607-481-826-0', 'Precálculo Matemáticas para el cálculo', 'James Stewart, Lothar Redlin, Saleem Watson', 'CENAGAGE Learning', 2, 2012),
	('978-607-481-826-0', 'Precálculo Matemáticas para el cálculo', 'James Stewart, Lothar Redlin, Saleem Watson', 'CENAGAGE Learning', 3, 2012),
	('978-607-481-826-0', 'Precálculo Matemáticas para el cálculo', 'James Stewart, Lothar Redlin, Saleem Watson', 'CENAGAGE Learning', 4, 2012),
	('978-607-481-826-0', 'Precálculo Matemáticas para el cálculo', 'James Stewart, Lothar Redlin, Saleem Watson', 'CENAGAGE Learning', 5, 2012),
	('978-607-481-826-0', 'Precálculo Matemáticas para el cálculo', 'James Stewart, Lothar Redlin, Saleem Watson', 'CENAGAGE Learning', 6, 2012),
	('978-607-481-826-0', 'Precálculo Matemáticas para el cálculo', 'James Stewart, Lothar Redlin, Saleem Watson', 'CENAGAGE Learning', 7, 2012),
	('978-607-481-826-0', 'Precálculo Matemáticas para el cálculo', 'James Stewart, Lothar Redlin, Saleem Watson', 'CENAGAGE Learning', 8, 2012),
	('978-607-481-826-0', 'Precálculo Matemáticas para el cálculo', 'James Stewart, Lothar Redlin, Saleem Watson', 'CENAGAGE Learning', 8, 2012),
	('978-607-481-826-0', 'Precálculo Matemáticas para el cálculo', 'James Stewart, Lothar Redlin, Saleem Watson', 'CENAGAGE Learning', 10, 2012);


INSERT INTO libro (isbn, titulo, autor, editorial, ejemplar, anio_publicacion) VALUES
	('9786070731747', 'Luna de Pluton', 'Angel David', 'Planeta', 1, 2015),
	('9786070731747', 'Luna de Pluton', 'Angel David', 'Planeta', 2, 2015),
	('9786070731747', 'Luna de Pluton', 'Angel David', 'Planeta', 3, 2015),
	('9786070731747', 'Luna de Pluton', 'Angel David', 'Planeta', 4, 2015),
	('9786070731747', 'Luna de Pluton', 'Angel David', 'Planeta', 5, 2015),
	('9786070731747', 'Luna de Pluton', 'Angel David', 'Planeta', 6, 2015),
	('9786070731747', 'Luna de Pluton', 'Angel David', 'Planeta', 7, 2015),
	('9786070731747', 'Luna de Pluton', 'Angel David', 'Planeta', 8, 2015),
	('9786070731747', 'Luna de Pluton', 'Angel David', 'Planeta', 9, 2015),
	('9786070731747', 'Luna de Pluton', 'Angel David', 'Planeta', 10, 2015);


INSERT INTO libro (isbn, titulo, autor, editorial, ejemplar, anio_publicacion) VALUES
	('9789876124232', 'Mazzer Runner', 'James Dashner', 'V y R', 1, 2012),
	('9789876124232', 'Mazzer Runner', 'James Dashner', 'V y R', 2, 2012),
	('9789876124232', 'Mazzer Runner', 'James Dashner', 'V y R', 3, 2012),
	('9789876124232', 'Mazzer Runner', 'James Dashner', 'V y R', 4, 2012),
	('9789876124232', 'Mazzer Runner', 'James Dashner', 'V y R', 5, 2012),
	('9789876124232', 'Mazzer Runner', 'James Dashner', 'V y R', 6, 2012),
	('9789876124232', 'Mazzer Runner', 'James Dashner', 'V y R', 7, 2012),
	('9789876124232', 'Mazzer Runner', 'James Dashner', 'V y R', 8, 2012),
	('9789876124232', 'Mazzer Runner', 'James Dashner', 'V y R', 9, 2012),
	('9789876124232', 'Mazzer Runner', 'James Dashner', 'V y R', 10, 2012);


INSERT INTO libro (isbn, titulo, autor, editorial, ejemplar, anio_publicacion) VALUES
	('7531689426538', 'La Torre Oscura', 'Stephen King', 'Donald M. Grant', 1, 1982),
	('7531689426538', 'La Torre Oscura', 'Stephen King', 'Donald M. Grant', 2, 1982),
	('7531689426538', 'La Torre Oscura', 'Stephen King', 'Donald M. Grant', 3, 1982),
	('7531689426538', 'La Torre Oscura', 'Stephen King', 'Donald M. Grant', 4, 1982),
	('7531689426538', 'La Torre Oscura', 'Stephen King', 'Donald M. Grant', 5, 1982),
	('7531689426538', 'La Torre Oscura', 'Stephen King', 'Donald M. Grant', 6, 1982),
	('7531689426538', 'La Torre Oscura', 'Stephen King', 'Donald M. Grant', 7, 1982),
	('7531689426538', 'La Torre Oscura', 'Stephen King', 'Donald M. Grant', 8, 1982),
	('7531689426538', 'La Torre Oscura', 'Stephen King', 'Donald M. Grant', 9, 1982),
	('7531689426538', 'La Torre Oscura', 'Stephen King', 'Donald M. Grant', 10, 1982);


INSERT INTO libro (isbn, titulo, autor, editorial, ejemplar, anio_publicacion) VALUES
	('978-607-15-0760-0', 'Álgebra Lineal', 'Stanley I. Grossman S., José Job Flores Godoy', 'McGraw-Hill', 1, 2012),
	('978-607-15-0760-0', 'Álgebra Lineal', 'Stanley I. Grossman S., José Job Flores Godoy', 'McGraw-Hill', 2, 2012),
	('978-607-15-0760-0', 'Álgebra Lineal', 'Stanley I. Grossman S., José Job Flores Godoy', 'McGraw-Hill', 3, 2012),
	('978-607-15-0760-0', 'Álgebra Lineal', 'Stanley I. Grossman S., José Job Flores Godoy', 'McGraw-Hill', 4, 2012),
	('978-607-15-0760-0', 'Álgebra Lineal', 'Stanley I. Grossman S., José Job Flores Godoy', 'McGraw-Hill', 5, 2012),
	('978-607-15-0760-0', 'Álgebra Lineal', 'Stanley I. Grossman S., José Job Flores Godoy', 'McGraw-Hill', 6, 2012),
	('978-607-15-0760-0', 'Álgebra Lineal', 'Stanley I. Grossman S., José Job Flores Godoy', 'McGraw-Hill', 7, 2012),
	('978-607-15-0760-0', 'Álgebra Lineal', 'Stanley I. Grossman S., José Job Flores Godoy', 'McGraw-Hill', 8, 2012),
	('978-607-15-0760-0', 'Álgebra Lineal', 'Stanley I. Grossman S., José Job Flores Godoy', 'McGraw-Hill', 9, 2012),
	('978-607-15-0760-0', 'Álgebra Lineal', 'Stanley I. Grossman S., José Job Flores Godoy', 'McGraw-Hill', 10, 2012);


INSERT INTO libro (isbn, titulo, autor, editorial, ejemplar, anio_publicacion) VALUES
	('978-0-13-459632-7', 'C# for programmers', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 1, 2016),
	('978-0-13-459632-7', 'C# for programmers', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 2, 2016),
	('978-0-13-459632-7', 'C# for programmers', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 3, 2016),
	('978-0-13-459632-7', 'C# for programmers', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 4, 2016),
	('978-0-13-459632-7', 'C# for programmers', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 5, 2016),
	('978-0-13-459632-7', 'C# for programmers', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 6, 2016),
	('978-0-13-459632-7', 'C# for programmers', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 7, 2016),
	('978-0-13-459632-7', 'C# for programmers', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 8, 2016),
	('978-0-13-459632-7', 'C# for programmers', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 9, 2016),
	('978-0-13-459632-7', 'C# for programmers', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 10, 2016);


INSERT INTO libro (isbn, titulo, autor, editorial, ejemplar, anio_publicacion) VALUES
	('978-607-32-2739-1', 'C++ Cómo programar', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 1, 2014),
	('978-607-32-2739-1', 'C++ Cómo programar', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 2, 2014),
	('978-607-32-2739-1', 'C++ Cómo programar', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 3, 2014),
	('978-607-32-2739-1', 'C++ Cómo programar', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 4, 2014),
	('978-607-32-2739-1', 'C++ Cómo programar', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 5, 2014),
	('978-607-32-2739-1', 'C++ Cómo programar', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 6, 2014),
	('978-607-32-2739-1', 'C++ Cómo programar', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 7, 2014),
	('978-607-32-2739-1', 'C++ Cómo programar', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 8, 2014),
	('978-607-32-2739-1', 'C++ Cómo programar', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 9, 2014),
	('978-607-32-2739-1', 'C++ Cómo programar', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 10, 2014);


INSERT INTO libro (isbn, titulo, autor, editorial, ejemplar, anio_publicacion) VALUES
	('970-26-0637-3', 'Matemáticas discretas', 'Richard Johnsonbaugh', 'Pearson educación', 1, 2005),
	('970-26-0637-3', 'Matemáticas discretas', 'Richard Johnsonbaugh', 'Pearson educación', 2, 2005),
	('970-26-0637-3', 'Matemáticas discretas', 'Richard Johnsonbaugh', 'Pearson educación', 3, 2005),
	('970-26-0637-3', 'Matemáticas discretas', 'Richard Johnsonbaugh', 'Pearson educación', 4, 2005),
	('970-26-0637-3', 'Matemáticas discretas', 'Richard Johnsonbaugh', 'Pearson educación', 5, 2005),
	('970-26-0637-3', 'Matemáticas discretas', 'Richard Johnsonbaugh', 'Pearson educación', 6, 2005),
	('970-26-0637-3', 'Matemáticas discretas', 'Richard Johnsonbaugh', 'Pearson educación', 7, 2005),
	('970-26-0637-3', 'Matemáticas discretas', 'Richard Johnsonbaugh', 'Pearson educación', 8, 2005),
	('970-26-0637-3', 'Matemáticas discretas', 'Richard Johnsonbaugh', 'Pearson educación', 9, 2005),
	('970-26-0637-3', 'Matemáticas discretas', 'Richard Johnsonbaugh', 'Pearson educación', 10, 2005);



/*LIBROS*/
/* Primer ejemplar */
59, 21, 31, 41, 50, 68, 11, 78

/*otros*/
10, 32, 9, 8, 60, 61, 62, 47, 48, 49, 51, 52, 53, ...

/*------------------*/
/*CLIENTES*/
/*Estudiantes*/
1, 4, 3, 12, 15, 1, 6, 17, ...

/*Profesores*/
22, 23, 21, 26, 27, 28

/*Ambos*/
29, 30, 31, 32, 33

/*-------------------------*/


INSERT INTO prestamo(codigo_libro, codigo_cliente, codigo_empleado, fecha_prestamo, fecha_entrega)
	VALUES (59, 1, 1, timestamp '2019-05-10 21:34:23', timestamp '2019-05-18 06:59:23'),
			(21, 4, 13, timestamp '2019-02-10 21:34:23', timestamp '2019-05-18 12:45:23'),
			(31, 22, 14, timestamp '2019-05-9 21:34:23', timestamp '2019-05-18 01:12:23'),
			(41, 23, 15, timestamp '2019-05-8 21:34:23', timestamp '2019-05-17 02:07:23'),
			(50, 33, 16, timestamp '2019-05-10 21:34:23', timestamp '2019-05-16 11:08:23'),
			(68, 29, 17, timestamp '2019-05-10 21:34:23', timestamp '2019-05-18 13:10:23'),

INSERT INTO prestamo(codigo_libro, codigo_cliente, codigo_empleado, fecha_prestamo, fecha_entrega)
			VALUES(10, 1, 1, timestamp '2019-05-01 21:34:23', timestamp '2019-05-01 11:10:23'),
			(32, 4, 1, timestamp '2019-05-02 21:34:23', timestamp '2019-05-02 02:10:23'),
			(9, 22, 1, timestamp '2019-05-03 21:34:23', timestamp '2019-05-03 11:10:23'),
			(8, 23, 1, timestamp '2019-05-04 21:34:23', timestamp '2019-05-04 15:10:23'),
			(60, 29, 1, timestamp '2019-05-10 21:34:23', timestamp '2019-05-05 17:10:23'),
			(61, 33, 1, timestamp '2019-05-10 21:34:23', timestamp '2019-05-06 12:07:00');
