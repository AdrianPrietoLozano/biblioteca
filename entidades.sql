
/*
*
*
IGNORAR ESTO
*
*
INSERT INTO usuario(nombre, telefono, departamento, carrera, grado, sexo, tipo)
	VALUES('Adrian', '12345', 'alguno', 'inni', '4', 'H', 'E');


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





SELECT codigo, nombre, telefono, departamento, carrera, grado, 
CASE WHEN sexo='H' THEN 'Hombre'
     WHEN sexo='M' THEN 'Mujer'
END AS sexo,
CASE WHEN tipo='E' THEN 'Estudiante'
     WHEN tipo='P' THEN 'Profesor'
     WHEN tipo='A' THEN 'Estudiante y profesor'
END AS tipoA
FROM cliente;




SELECT * , EXTRACT( days from to_timestamp(CAST(fecha_entrega as varchar), 'yyyy-mm-dd') - to_timestamp(CAST(now() AS VARCHAR), 'yyyy-mm-dd') )
FROM prestamo;


SELECT * , EXTRACT( days from fecha_entrega - now() )
FROM prestamo;



SELECT codigo, titulo, nombre_cliente, nombre_empleado, fecha_prestamo, fecha_entrega,
	CASE WHEN ejemplar = 1 THEN CONCAT(CAST(retraso / 3600 as INT), ' horas')
		 WHEN ejemplar <> 1 THEN CONCAT(CAST(retraso / 86400 as INT), ' días')
	END AS retraso2,
	CASE WHEN ejemplar = 1 THEN (retraso / 3600) * 1
		 WHEN ejemplar <> 1 THEN (retraso / 86400) * 5
	END AS penalizacion2

	FROM

(SELECT prestamo.codigo, titulo, cliente.nombre AS nombre_cliente, empleado.nombre AS nombre_empleado,
		fecha_prestamo, fecha_entrega, ejemplar,
	CASE WHEN EXTRACT( EPOCH from now() - fecha_entrega ) <= 0 THEN 0
         WHEN EXTRACT( EPOCH from now() - fecha_entrega ) > 0 THEN EXTRACT( EPOCH from now() - fecha_entrega )
    END AS retraso
    FROM prestamo LEFT JOIN libro ON libro.codigo=codigo_libro
    LEFT JOIN cliente ON cliente.codigo=codigo_cliente
    LEFT JOIN empleado ON empleado.codigo=codigo_empleado) AS temporal;