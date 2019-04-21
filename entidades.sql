CREATE TABLE prestamo(
	codigo SERIAL PRIMARY KEY UNIQUE NOT NULL,
	codigo_libro INTEGER UNIQUE NOT NULL,
	codigo_cliente INTEGER NOT NULL,
	codigo_empleado INTEGER NOT NULL,
	fecha_prestamo TIMESTAMP,
	fecha_entrega TIMESTAMP,
	penalizacion DECIMAL DEFAULT 0.0
);

CREATE TABLE usuario(
	codigo SERIAL PRIMARY KEY UNIQUE NOT NULL,
	nombre VARCHAR(100) NOT NULL,
	telefono VARCHAR(25),
	departamento VARCHAR(100),
	carrera VARCHAR(50),
	grado INTEGER,
	sexo CHAR(1),
	tipo CHAR(1)
);


CREATE TABLE empleado(
	codigo SERIAL PRIMARY KEY UNIQUE NOT NULL,
	nombre VARCHAR(100) NOT NULL,
	nombre_usuario VARCHAR(30) UNIQUE NOT NULL,
	contrasenia BYTEA NOT NULL,
	edad INTEGER,
	salario DECIMAL,
	sexo CHAR(1)
);

INSERT INTO empleado(nombre, nombre_usuario, contrasenia, edad, salario, sexo)
VALUES('Equipo 7', 'equipo 7', PGP_SYM_ENCRYPT('12345', 'equipo7'),
    	20, 1000, 'H'
);


INSERT INTO usuario(nombre, telefono, departamento, carrera, grado, sexo, tipo)
	VALUES('Adrian', '12345', 'alguno', 'inni', '4', 'H', 'E');


INSERT INTO prestamo(codigo_libro, codigo_cliente, codigo_empleado, fecha_prestamo)
	VALUES(1, 2, 3, "")


SELECT usuario.tipo AS tipo, count(prestamo.codigo) AS num_prestamos
	FROM usuario, prestamo WHERE usuario.codigo=1
		AND prestamo.codigo_cliente=1 GROUP BY usuario.tipo


SELECT nombre, nombre_usuario, PGP_SYM_DECRYPT(contrasenia, 'equipo7') FROM empleado;