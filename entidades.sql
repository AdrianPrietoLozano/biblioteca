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

INSERT INTO libro (isbn, titulo, autor, editorial, ejemplar, anio_publicacion) VALUES
	('978-607-32-3802-1', 'Cómo programar en Java', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 1, 2016),
	('978-607-32-3802-1', 'Cómo programar en Java', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 2, 2016),
	('978-607-32-3802-1', 'Cómo programar en Java', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 3, 2016),
	('978-607-32-3802-1', 'Cómo programar en Java', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 4, 2016),
	('978-607-32-3802-1', 'Cómo programar en Java', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 5, 2016),
	('978-607-32-3802-1', 'Cómo programar en Java', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 6, 2016),
	('978-607-32-3802-1', 'Cómo programar en Java', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 7, 2016),
	('978-607-32-3802-1', 'Cómo programar en Java', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 8, 2016),
	('978-607-32-3802-1', 'Cómo programar en Java', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 9, 2016),
	('978-607-32-3802-1', 'Cómo programar en Java', 'Paul Deitel, Harvey Deitel', 'Pearson educación', 10, 2016);


INSERT INTO libro (isbn, titulo, autor, editorial, ejemplar, anio_publicacion) VALUES
	('0-13-177429-8', 'Expert C Programming', 'Peter van der Linden', 'SunSoft Press', '1', '1994'),
	('0-13-177429-8', 'Expert C Programming', 'Peter van der Linden', 'SunSoft Press', '2', '1994'),
	('0-13-177429-8', 'Expert C Programming', 'Peter van der Linden', 'SunSoft Press', '3', '1994'),
	('0-13-177429-8', 'Expert C Programming', 'Peter van der Linden', 'SunSoft Press', '4', '1994'),
	('0-13-177429-8', 'Expert C Programming', 'Peter van der Linden', 'SunSoft Press', '5', '1994'),
	('0-13-177429-8', 'Expert C Programming', 'Peter van der Linden', 'SunSoft Press', '6', '1994'),
	('0-13-177429-8', 'Expert C Programming', 'Peter van der Linden', 'SunSoft Press', '7', '1994'),
	('0-13-177429-8', 'Expert C Programming', 'Peter van der Linden', 'SunSoft Press', '8', '1994'),
	('0-13-177429-8', 'Expert C Programming', 'Peter van der Linden', 'SunSoft Press', '9', '1994'),
	('0-13-177429-8', 'Expert C Programming', 'Peter van der Linden', 'SunSoft Press', '10', '1994');


INSERT INTO libro (isbn, titulo, autor, editorial, ejemplar, anio_publicacion) VALUES
	('978-1-59327-603-4', 'Python Crash Course', 'Eric Matthes', 'No Starch Press', 1, 2015),
	('978-1-59327-603-4', 'Python Crash Course', 'Eric Matthes', 'No Starch Press', 2, 2015),
	('978-1-59327-603-4', 'Python Crash Course', 'Eric Matthes', 'No Starch Press', 3, 2015),
	('978-1-59327-603-4', 'Python Crash Course', 'Eric Matthes', 'No Starch Press', 4, 2015),
	('978-1-59327-603-4', 'Python Crash Course', 'Eric Matthes', 'No Starch Press', 5, 2015),
	('978-1-59327-603-4', 'Python Crash Course', 'Eric Matthes', 'No Starch Press', 6, 2015),
	('978-1-59327-603-4', 'Python Crash Course', 'Eric Matthes', 'No Starch Press', 7, 2015),
	('978-1-59327-603-4', 'Python Crash Course', 'Eric Matthes', 'No Starch Press', 8, 2015),
	('978-1-59327-603-4', 'Python Crash Course', 'Eric Matthes', 'No Starch Press', 9, 2015),
	('978-1-59327-603-4', 'Python Crash Course', 'Eric Matthes', 'No Starch Press', 10, 2015);


INSERT INTO libro (isbn, titulo, autor, editorial, ejemplar, anio_publicacion) VALUES
	('978-607-32-0603-7', 'Ingeniería de software', 'Ian Sommerville', 'Pearson educación', 1, 2011),
	('978-607-32-0603-7', 'Ingeniería de software', 'Ian Sommerville', 'Pearson educación', 2, 2011),
	('978-607-32-0603-7', 'Ingeniería de software', 'Ian Sommerville', 'Pearson educación', 3, 2011),
	('978-607-32-0603-7', 'Ingeniería de software', 'Ian Sommerville', 'Pearson educación', 4, 2011),
	('978-607-32-0603-7', 'Ingeniería de software', 'Ian Sommerville', 'Pearson educación', 5, 2011),
	('978-607-32-0603-7', 'Ingeniería de software', 'Ian Sommerville', 'Pearson educación', 6, 2011),
	('978-607-32-0603-7', 'Ingeniería de software', 'Ian Sommerville', 'Pearson educación', 7, 2011),
	('978-607-32-0603-7', 'Ingeniería de software', 'Ian Sommerville', 'Pearson educación', 8, 2011),
	('978-607-32-0603-7', 'Ingeniería de software', 'Ian Sommerville', 'Pearson educación', 9, 2011),
	('978-607-32-0603-7', 'Ingeniería de software', 'Ian Sommerville', 'Pearson educación', 10, 2011);


INSERT INTO libro (isbn, titulo, autor, editorial, ejemplar, anio_publicacion) VALUES
	('968-880-205-0', 'El lenguaje de programacion C', 'Brian W. Kernighan, Dennis M. Ritchie', 'Pearson educacion', 1, 1991),
	('968-880-205-0', 'El lenguaje de programacion C', 'Brian W. Kernighan, Dennis M. Ritchie', 'Pearson educacion', 2, 1991),
	('968-880-205-0', 'El lenguaje de programacion C', 'Brian W. Kernighan, Dennis M. Ritchie', 'Pearson educacion', 3, 1991),
	('968-880-205-0', 'El lenguaje de programacion C', 'Brian W. Kernighan, Dennis M. Ritchie', 'Pearson educacion', 4, 1991),
	('968-880-205-0', 'El lenguaje de programacion C', 'Brian W. Kernighan, Dennis M. Ritchie', 'Pearson educacion', 5, 1991),
	('968-880-205-0', 'El lenguaje de programacion C', 'Brian W. Kernighan, Dennis M. Ritchie', 'Pearson educacion', 6, 1991),
	('968-880-205-0', 'El lenguaje de programacion C', 'Brian W. Kernighan, Dennis M. Ritchie', 'Pearson educacion', 7, 1991),
	('968-880-205-0', 'El lenguaje de programacion C', 'Brian W. Kernighan, Dennis M. Ritchie', 'Pearson educacion', 8, 1991),
	('968-880-205-0', 'El lenguaje de programacion C', 'Brian W. Kernighan, Dennis M. Ritchie', 'Pearson educacion', 9, 1991),
	('968-880-205-0', 'El lenguaje de programacion C', 'Brian W. Kernighan, Dennis M. Ritchie', 'Pearson educacion', 10, 1991);


INSERT INTO libro (isbn, titulo, autor, editorial, ejemplar, anio_publicacion) VALUES
	('978-1-449-34037-7', 'Python Cookbook', 'David Beazley, Brian K. Jones', 'O''REILLY', 1, 2013),
	('978-1-449-34037-7', 'Python Cookbook', 'David Beazley, Brian K. Jones', 'O''REILLY', 2, 2013),
	('978-1-449-34037-7', 'Python Cookbook', 'David Beazley, Brian K. Jones', 'O''REILLY', 3, 2013),
	('978-1-449-34037-7', 'Python Cookbook', 'David Beazley, Brian K. Jones', 'O''REILLY', 4, 2013),
	('978-1-449-34037-7', 'Python Cookbook', 'David Beazley, Brian K. Jones', 'O''REILLY', 5, 2013),
	('978-1-449-34037-7', 'Python Cookbook', 'David Beazley, Brian K. Jones', 'O''REILLY', 6, 2013),
	('978-1-449-34037-7', 'Python Cookbook', 'David Beazley, Brian K. Jones', 'O''REILLY', 7, 2013),
	('978-1-449-34037-7', 'Python Cookbook', 'David Beazley, Brian K. Jones', 'O''REILLY', 8, 2013),
	('978-1-449-34037-7', 'Python Cookbook', 'David Beazley, Brian K. Jones', 'O''REILLY', 9, 2013),
	('978-1-449-34037-7', 'Python Cookbook', 'David Beazley, Brian K. Jones', 'O''REILLY', 10, 2013);

INSERT INTO libro (isbn, titulo, autor, editorial, ejemplar, anio_publicacion) VALUES
	('978-970-26-0795-3', 'Física conceptual', 'Paul G. Hewitt', 'Pearson educación', 1, 2007),
	('978-970-26-0795-3', 'Física conceptual', 'Paul G. Hewitt', 'Pearson educación', 2, 2007),
	('978-970-26-0795-3', 'Física conceptual', 'Paul G. Hewitt', 'Pearson educación', 3, 2007),
	('978-970-26-0795-3', 'Física conceptual', 'Paul G. Hewitt', 'Pearson educación', 4, 2007),
	('978-970-26-0795-3', 'Física conceptual', 'Paul G. Hewitt', 'Pearson educación', 5, 2007),
	('978-970-26-0795-3', 'Física conceptual', 'Paul G. Hewitt', 'Pearson educación', 6, 2007),
	('978-970-26-0795-3', 'Física conceptual', 'Paul G. Hewitt', 'Pearson educación', 7, 2007),
	('978-970-26-0795-3', 'Física conceptual', 'Paul G. Hewitt', 'Pearson educación', 8, 2007),
	('978-970-26-0795-3', 'Física conceptual', 'Paul G. Hewitt', 'Pearson educación', 9, 2007),
	('978-970-26-0795-3', 'Física conceptual', 'Paul G. Hewitt', 'Pearson educación', 10, 2007);


INSERT INTO libro (isbn, titulo, autor, editorial, ejemplar, anio_publicacion) VALUES
	('978-1-4302-1912-5', 'Pro Linux System Administration', 'James Turnbull, Peter Lieverdink, Dennis Matotek', 'Apress', 1, 2009),
	('978-1-4302-1912-5', 'Pro Linux System Administration', 'James Turnbull, Peter Lieverdink, Dennis Matotek', 'Apress', 2, 2009),
	('978-1-4302-1912-5', 'Pro Linux System Administration', 'James Turnbull, Peter Lieverdink, Dennis Matotek', 'Apress', 3, 2009),
	('978-1-4302-1912-5', 'Pro Linux System Administration', 'James Turnbull, Peter Lieverdink, Dennis Matotek', 'Apress', 4, 2009),
	('978-1-4302-1912-5', 'Pro Linux System Administration', 'James Turnbull, Peter Lieverdink, Dennis Matotek', 'Apress', 5, 2009),
	('978-1-4302-1912-5', 'Pro Linux System Administration', 'James Turnbull, Peter Lieverdink, Dennis Matotek', 'Apress', 6, 2009),
	('978-1-4302-1912-5', 'Pro Linux System Administration', 'James Turnbull, Peter Lieverdink, Dennis Matotek', 'Apress', 7, 2009),
	('978-1-4302-1912-5', 'Pro Linux System Administration', 'James Turnbull, Peter Lieverdink, Dennis Matotek', 'Apress', 8, 2009),
	('978-1-4302-1912-5', 'Pro Linux System Administration', 'James Turnbull, Peter Lieverdink, Dennis Matotek', 'Apress', 9, 2009),
	('978-1-4302-1912-5', 'Pro Linux System Administration', 'James Turnbull, Peter Lieverdink, Dennis Matotek', 'Apress', 10, 2009);


INSERT INTO libro (isbn, titulo, autor, editorial, ejemplar, anio_publicacion) VALUES
	('978-1-4302-1889-0', 'Beginning the Linux Command Line', 'Sander van Vugt', 'Apress', 1, 2009),
	('978-1-4302-1889-0', 'Beginning the Linux Command Line', 'Sander van Vugt', 'Apress', 2, 2009),
	('978-1-4302-1889-0', 'Beginning the Linux Command Line', 'Sander van Vugt', 'Apress', 3, 2009),
	('978-1-4302-1889-0', 'Beginning the Linux Command Line', 'Sander van Vugt', 'Apress', 4, 2009),
	('978-1-4302-1889-0', 'Beginning the Linux Command Line', 'Sander van Vugt', 'Apress', 5, 2009),
	('978-1-4302-1889-0', 'Beginning the Linux Command Line', 'Sander van Vugt', 'Apress', 6, 2009),
	('978-1-4302-1889-0', 'Beginning the Linux Command Line', 'Sander van Vugt', 'Apress', 7, 2009),
	('978-1-4302-1889-0', 'Beginning the Linux Command Line', 'Sander van Vugt', 'Apress', 8, 2009),
	('978-1-4302-1889-0', 'Beginning the Linux Command Line', 'Sander van Vugt', 'Apress', 9, 2009),
	('978-1-4302-1889-0', 'Beginning the Linux Command Line', 'Sander van Vugt', 'Apress', 10, 2009);


INSERT INTO libro (isbn, titulo, autor, editorial, ejemplar, anio_publicacion) VALUES
	('978-84-205-4110-5', 'Comunicaciones y Redes de Computadores', 'William Stallings', 'Pearson educacion', 1, 2004),
	('978-84-205-4110-5', 'Comunicaciones y Redes de Computadores', 'William Stallings', 'Pearson educacion', 2, 2004),
	('978-84-205-4110-5', 'Comunicaciones y Redes de Computadores', 'William Stallings', 'Pearson educacion', 3, 2004),
	('978-84-205-4110-5', 'Comunicaciones y Redes de Computadores', 'William Stallings', 'Pearson educacion', 4, 2004),
	('978-84-205-4110-5', 'Comunicaciones y Redes de Computadores', 'William Stallings', 'Pearson educacion', 5, 2004),
	('978-84-205-4110-5', 'Comunicaciones y Redes de Computadores', 'William Stallings', 'Pearson educacion', 6, 2004),
	('978-84-205-4110-5', 'Comunicaciones y Redes de Computadores', 'William Stallings', 'Pearson educacion', 7, 2004),
	('978-84-205-4110-5', 'Comunicaciones y Redes de Computadores', 'William Stallings', 'Pearson educacion', 8, 2004),
	('978-84-205-4110-5', 'Comunicaciones y Redes de Computadores', 'William Stallings', 'Pearson educacion', 9, 2004),
	('978-84-205-4110-5', 'Comunicaciones y Redes de Computadores', 'William Stallings', 'Pearson educacion', 10, 2004);




/*
*
*
*
*
*
IGNORAR ESTO
*
*
*
*
---------------------------------------------------------

SELECT codigo, nombre, nombre_usuario, PGP_SYM_DECRYPT(contrasenia, 'equipo7'),
	edad, salario, sexo FROM empleado;

--------------------------------------------------------------------------
SELECT codigo, nombre, telefono, departamento, carrera, grado, sexo, tipo
FROM (SELECT codigo, nombre, telefono, departamento, carrera, grado,
	CASE WHEN sexo='H' THEN 'Hombre'
     	WHEN sexo='M' THEN 'Mujer'
	END AS sexo,
	CASE WHEN tipo='E' THEN 'Estudiante'
     	WHEN tipo='P' THEN 'Profesor'
     	WHEN tipo='A' THEN 'Ambos'
	END AS tipo FROM cliente) AS temporal

--------------------------------------------------

SELECT * , EXTRACT( days from to_timestamp(CAST(fecha_entrega as varchar), 'yyyy-mm-dd') - to_timestamp(CAST(now() AS VARCHAR), 'yyyy-mm-dd') )
FROM prestamo;

-------------------------------------


INSERT INTO prestamo(codigo_libro, codigo_cliente, codigo_empleado, fecha_prestamo, fecha_entrega)
VALUES (5, 1, 1, timestamp '2019-05-11 21:34:23', timestamp '2019-05-11 21:34:23');

----------------------------------------------------------------------------


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


----------------------------------------------------------------------------------

CASE
	WHEN ejemplar = 1 AND EXTRACT( EPOCH from now() - fecha_entrega ) <= 0 THEN 0
	WHEN ejemplar = 1 AND EXTRACT( EPOCH from now() - fecha_entrega ) > 0
		THEN EXTRACT( EPOCH from now() - fecha_entrega )
	WHEN ejemplar <> 1 AND EXTRACT( EPOCH from now() - (fecha_entrega - interval '24 hours') ) <= 0 THEN 0
	WHEN ejemplar <> 1 AND EXTRACT( EPOCH from now() - (fecha_entrega - interval '24 hours') ) > 0
		THEN EXTRACT( EPOCH from now() - (fecha_entrega - interval '24 hours') )
END AS retraso	

----------------------------------------------------------------------------

SELECT L.titulo, L.ejemplar, C.nombre, CASE WHEN C.tipo='E' THEN 'Estudiante' 
     	WHEN C.tipo='P' THEN 'Profesor' 
     	WHEN C.tipo='A' THEN 'Estudiante y profesor' END AS tipo, fecha_entrega 
FROM prestamo AS P LEFT JOIN libro AS L ON L.codigo=codigo_libro 
			LEFT JOIN cliente AS C ON C.codigo=codigo_cliente 
WHERE P.codigo=?

------------------------------------------------------------------------------

*/

