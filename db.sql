--
-- PostgreSQL database dump
--

-- Dumped from database version 10.7
-- Dumped by pg_dump version 10.7

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'LATIN1';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


--
-- Name: pgcrypto; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS pgcrypto WITH SCHEMA public;


--
-- Name: EXTENSION pgcrypto; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION pgcrypto IS 'cryptographic functions';


SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: cliente; Type: TABLE; Schema: public; Owner: adrian
--

CREATE TABLE public.cliente (
    codigo integer NOT NULL,
    nombre character varying(100) NOT NULL,
    telefono character varying(25),
    departamento character varying(100),
    carrera character varying(50),
    grado integer,
    sexo character(1),
    tipo character(1) DEFAULT 'E'::bpchar,
    CONSTRAINT sexo CHECK ((sexo = ANY (ARRAY['H'::bpchar, 'M'::bpchar]))),
    CONSTRAINT tipo CHECK ((tipo = ANY (ARRAY['E'::bpchar, 'P'::bpchar, 'A'::bpchar])))
);


ALTER TABLE public.cliente OWNER TO adrian;

--
-- Name: empleado; Type: TABLE; Schema: public; Owner: adrian
--

CREATE TABLE public.empleado (
    codigo integer NOT NULL,
    nombre character varying(100) NOT NULL,
    nombre_usuario character varying(30) NOT NULL,
    contrasenia bytea NOT NULL,
    edad integer,
    salario numeric,
    sexo character(1),
    es_administrador boolean DEFAULT false NOT NULL,
    CONSTRAINT sexo CHECK ((sexo = ANY (ARRAY['H'::bpchar, 'M'::bpchar])))
);


ALTER TABLE public.empleado OWNER TO adrian;

--
-- Name: empleado_codigo_seq; Type: SEQUENCE; Schema: public; Owner: adrian
--

CREATE SEQUENCE public.empleado_codigo_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.empleado_codigo_seq OWNER TO adrian;

--
-- Name: empleado_codigo_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: adrian
--

ALTER SEQUENCE public.empleado_codigo_seq OWNED BY public.empleado.codigo;


--
-- Name: libro; Type: TABLE; Schema: public; Owner: adrian
--

CREATE TABLE public.libro (
    codigo integer NOT NULL,
    isbn character varying(30) NOT NULL,
    titulo character varying(100) NOT NULL,
    autor character varying(100),
    editorial character varying(100),
    ejemplar integer NOT NULL,
    anio_publicacion integer
);


ALTER TABLE public.libro OWNER TO adrian;

--
-- Name: libro_codigo_libro_seq; Type: SEQUENCE; Schema: public; Owner: adrian
--

CREATE SEQUENCE public.libro_codigo_libro_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.libro_codigo_libro_seq OWNER TO adrian;

--
-- Name: libro_codigo_libro_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: adrian
--

ALTER SEQUENCE public.libro_codigo_libro_seq OWNED BY public.libro.codigo;


--
-- Name: prestamo; Type: TABLE; Schema: public; Owner: adrian
--

CREATE TABLE public.prestamo (
    codigo integer NOT NULL,
    codigo_libro integer NOT NULL,
    codigo_cliente integer NOT NULL,
    codigo_empleado integer NOT NULL,
    fecha_prestamo timestamp without time zone NOT NULL,
    fecha_entrega timestamp without time zone NOT NULL
);


ALTER TABLE public.prestamo OWNER TO adrian;

--
-- Name: prestamo_codigo_seq; Type: SEQUENCE; Schema: public; Owner: adrian
--

CREATE SEQUENCE public.prestamo_codigo_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.prestamo_codigo_seq OWNER TO adrian;

--
-- Name: prestamo_codigo_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: adrian
--

ALTER SEQUENCE public.prestamo_codigo_seq OWNED BY public.prestamo.codigo;


--
-- Name: usuario_codigo_seq; Type: SEQUENCE; Schema: public; Owner: adrian
--

CREATE SEQUENCE public.usuario_codigo_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.usuario_codigo_seq OWNER TO adrian;

--
-- Name: usuario_codigo_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: adrian
--

ALTER SEQUENCE public.usuario_codigo_seq OWNED BY public.cliente.codigo;


--
-- Name: cliente codigo; Type: DEFAULT; Schema: public; Owner: adrian
--

ALTER TABLE ONLY public.cliente ALTER COLUMN codigo SET DEFAULT nextval('public.usuario_codigo_seq'::regclass);


--
-- Name: empleado codigo; Type: DEFAULT; Schema: public; Owner: adrian
--

ALTER TABLE ONLY public.empleado ALTER COLUMN codigo SET DEFAULT nextval('public.empleado_codigo_seq'::regclass);


--
-- Name: libro codigo; Type: DEFAULT; Schema: public; Owner: adrian
--

ALTER TABLE ONLY public.libro ALTER COLUMN codigo SET DEFAULT nextval('public.libro_codigo_libro_seq'::regclass);


--
-- Name: prestamo codigo; Type: DEFAULT; Schema: public; Owner: adrian
--

ALTER TABLE ONLY public.prestamo ALTER COLUMN codigo SET DEFAULT nextval('public.prestamo_codigo_seq'::regclass);


--
-- Data for Name: cliente; Type: TABLE DATA; Schema: public; Owner: adrian
--

COPY public.cliente (codigo, nombre, telefono, departamento, carrera, grado, sexo, tipo) FROM stdin;
3	Ramón López Pérez	3333568249	Electrónica y computación	INCO	4	H	E
17	Karen Martí­nez López	3331456672	Electrónica y computación	INRO	5	M	E
19	Marí­a Rodriguez López	3423454323	Electrónica y computación	INRO	5	M	E
21	Karina Ponce López	3312453423	Electrónica y computación	INCO	6	M	P
26	Martí­n Arturo Garcí­a González	3331249087	Electrónica y computación		0	H	P
4	Federico Esparza Gallardo	7865434567	Electrónica y computación	INCO	5	H	E
12	Edgar Prieto Lozano	2324346724	Electrónica y computación	INNI	6	H	E
15	Fabian Delgadillo Lozano	3454345678	Electrónica y computación	INNI	5	H	E
16	Bertha Aguilar Esparza	3332678901	Electrónica y computación	INRO	6	M	E
20	Evelyn Prieto Lozano	3321234567	Electrónica y computación	INCO	4	M	E
18	Sofia Esparza Prieto	3341344536	Electrónica y computación	INNI	5	M	E
22	Luis Felipe Mariscal Lugo	3312342314	Electrónica y computación		0	H	P
23	Michel Davalos Boites	3133245463	Electrónica y computación		0	H	P
30	Omar Aguayo Ponce	3334521234	Electrónica y computación	INRO	5	H	A
1	Adrián Prieto Lozano	3331563410	Electrónica y computación	INNI	4	H	E
27	Elsa Estrada Guzmán	3234534561	Electrónica y computación		0	M	P
28	Marí­a Magdalena Murillo Leaño	3232343212	Electrónica y computación		0	M	P
29	Juan López Prieto	3323132435	Electrónica y computación	INNI	7	H	A
31	Sara Garcí­a Estrada	3320900980	Electrónica y computación	INNI	3	M	A
32	Refugio Prieto López	3324516748	Electrónica y computación	INCO	2	M	A
33	Griselda Pérez Torres	331324500098	Electrónica y computación	INNI	2	M	A
\.


--
-- Data for Name: empleado; Type: TABLE DATA; Schema: public; Owner: adrian
--

COPY public.empleado (codigo, nombre, nombre_usuario, contrasenia, edad, salario, sexo, es_administrador) FROM stdin;
1	Equipo 7	equipo 7	\\xc30d040703022b3ee05b66d5706f74d2360171c89de989239ad93f03cccf0cf61011a5c566e49514f1bc55ff6d5e4cc5dc8f97acbb93a6587a1a7fb5ac3c74b6d6e13fde4111ee	20	1000	H	t
15	Juan Flores Gallardo	juan	\\xc30d04070302fbd9a2421144492f6cd235012ca73e5f047902b63f1ed31899e06f3c4adaf0555057a63d2fdc044f651ef026a8a5b508d84845ba49cbbd3d42df0db79027e3b3	20	5000.00	H	f
17	Edgar Aguilar Esparza	edgar	\\xc30d04070302b96c6496eec72ae676d236015c3d8a6339939d611eea3eb0e29ad2a5324ab9b8e7774a6840b8bcfcdc9f5583307509844dac9a16a16ccedc53ebddd3352f80bbca	45	5000.00	H	f
19	Daniela	daniela	\\xc30d0407030224b0e1527b86ee2f7fd23801415532f9c8a422a1edb44e466bf39c76ded12bb97c1756b29a4df275145eed41547fbbaff919564d9b37709090e04f0b2b02e62eb20d68	22	5000	M	f
21	Omar Aguayo Delgadillo	omar	\\xc30d040703022fd822138f6b946e6fd23501846520dc93e5839276f6629bcf93fc9456685baaab594203a630a9f9f2882830602b821121361d92d7603e4afedfaf41d2e9ee0e	20	5000.00	H	f
12	Ramón López Pérez	ramon	\\xc30d0407030214cc376f0408756968d23601350e627178a51db871eded2a09bf60906ee5cd7b94d98bebb579f31acbdc0b987a21caa4e8b2e98c8d2c1211a7cab97e0e6b478ba8	24	5000	H	f
14	Sofia Ramí­rez Prieto	sofia	\\xc30d0407030245862394ff299c8d6dd23601b01f9459476edd4b113e727ac10842d4fb7681a8e8baa064bca43cb416173d2661f6db76665028dc3088af3ada7e3588e4594185f3	50	5000	M	f
13	Evelyn Ponce López	evelyn	\\xc30d04070302a3dc2dcd0603f1fd77d2370105d98556041181301f362b0a10a9348a7a40a511bd476046a74be033e9eeee97492076c966e83a9d39f8be7ea198ad8d9bd494136462	34	5000	M	f
16	Pablo Pérez Lozano	pablo	\\xc30d04070302f0999f2a4232ed8568d236011984f44c6aa4916549d5c417121e24907661801d75e7f926386adb14fd76e105e7144bbd076e0ae8f326633e8b7969bb52d7d5ef52	34	5000	H	f
18	Alicia Ramírez Ponce	alicia	\\xc30d04070302673b641a335c31d765d2370147a200fe38075ad8919400356a43c0e2db20d4cc745769b51e45d3d0d0371a8c8bb499536c6c1ccca89245fc5cf76edc946426e07b21	23	5000	M	f
20	Sandra Palafox Sánchez	sandra	\\xc30d0407030243273ecf696df2ce6fd2370133c41e1b97ce438bca03fb75f28796b980fdfb004e8f9d8162edfe2cba6538f7f8307e652c95fbbe9b9d5438e8af554649ddc593bab5	25	5000	M	f
\.


--
-- Data for Name: libro; Type: TABLE DATA; Schema: public; Owner: adrian
--

COPY public.libro (codigo, isbn, titulo, autor, editorial, ejemplar, anio_publicacion) FROM stdin;
127	978-607-32-3802-1	Cómo programar en Java	Paul Deitel, Harvey Deitel	Pearson educación	1	2016
10	9789876124232	Mazzer Runner	James Dashner	V y R	12	2012
9	7531689426538	La Torre Oscura	Stephen King	Donald M. Grant	3	1982
8	9786070731747	Luna de Pluton	Angel David	Planeta	5	2015
59	7531689426538	La Torre Oscura	Stephen King	Donald M. Grant	1	1982
60	7531689426538	La Torre Oscura	Stephen King	Donald M. Grant	2	1982
61	7531689426538	La Torre Oscura	Stephen King	Donald M. Grant	4	1982
157	978-607-32-0603-7	Ingeniería de software	Ian Sommerville	Pearson educación	1	2011
158	978-607-32-0603-7	Ingeniería de software	Ian Sommerville	Pearson educación	2	2011
159	978-607-32-0603-7	Ingeniería de software	Ian Sommerville	Pearson educación	3	2011
160	978-607-32-0603-7	Ingeniería de software	Ian Sommerville	Pearson educación	4	2011
161	978-607-32-0603-7	Ingeniería de software	Ian Sommerville	Pearson educación	5	2011
162	978-607-32-0603-7	Ingeniería de software	Ian Sommerville	Pearson educación	6	2011
163	978-607-32-0603-7	Ingeniería de software	Ian Sommerville	Pearson educación	7	2011
164	978-607-32-0603-7	Ingeniería de software	Ian Sommerville	Pearson educación	8	2011
165	978-607-32-0603-7	Ingeniería de software	Ian Sommerville	Pearson educación	9	2011
21	9786073157063	It	Stephen King	Viking Press	1	1986
22	9786073157063	It	Stephen King	Viking Press	2	1986
23	9786073157063	It	Stephen King	Viking Press	3	1986
24	9786073157063	It	Stephen King	Viking Press	4	1986
25	9786073157063	It	Stephen King	Viking Press	5	1986
26	9786073157063	It	Stephen King	Viking Press	6	1986
27	9786073157063	It	Stephen King	Viking Press	7	1986
28	9786073157063	It	Stephen King	Viking Press	8	1986
29	9786073157063	It	Stephen King	Viking Press	9	1986
30	9786073157063	It	Stephen King	Viking Press	10	1986
166	978-607-32-0603-7	Ingeniería de software	Ian Sommerville	Pearson educación	10	2011
178	978-1-449-34037-7	Python Cookbook	David Beazley, Brian K. Jones	O'REILLY	1	2013
179	978-1-449-34037-7	Python Cookbook	David Beazley, Brian K. Jones	O'REILLY	2	2013
180	978-1-449-34037-7	Python Cookbook	David Beazley, Brian K. Jones	O'REILLY	3	2013
181	978-1-449-34037-7	Python Cookbook	David Beazley, Brian K. Jones	O'REILLY	4	2013
182	978-1-449-34037-7	Python Cookbook	David Beazley, Brian K. Jones	O'REILLY	5	2013
183	978-1-449-34037-7	Python Cookbook	David Beazley, Brian K. Jones	O'REILLY	6	2013
184	978-1-449-34037-7	Python Cookbook	David Beazley, Brian K. Jones	O'REILLY	7	2013
185	978-1-449-34037-7	Python Cookbook	David Beazley, Brian K. Jones	O'REILLY	8	2013
186	978-1-449-34037-7	Python Cookbook	David Beazley, Brian K. Jones	O'REILLY	9	2013
41	9786070731747	Luna de Pluton	Angel David	Planeta	1	2015
42	9786070731747	Luna de Pluton	Angel David	Planeta	2	2015
43	9786070731747	Luna de Pluton	Angel David	Planeta	3	2015
44	9786070731747	Luna de Pluton	Angel David	Planeta	4	2015
45	9786070731747	Luna de Pluton	Angel David	Planeta	5	2015
46	9786070731747	Luna de Pluton	Angel David	Planeta	6	2015
47	9786070731747	Luna de Pluton	Angel David	Planeta	7	2015
48	9786070731747	Luna de Pluton	Angel David	Planeta	9	2015
49	9786070731747	Luna de Pluton	Angel David	Planeta	10	2015
50	9789876124232	Mazzer Runner	James Dashner	V y R	1	2012
51	9789876124232	Mazzer Runner	James Dashner	V y R	2	2012
52	9789876124232	Mazzer Runner	James Dashner	V y R	3	2012
53	9789876124232	Mazzer Runner	James Dashner	V y R	4	2012
54	9789876124232	Mazzer Runner	James Dashner	V y R	5	2012
55	9789876124232	Mazzer Runner	James Dashner	V y R	6	2012
56	9789876124232	Mazzer Runner	James Dashner	V y R	7	2012
57	9789876124232	Mazzer Runner	James Dashner	V y R	8	2012
58	9789876124232	Mazzer Runner	James Dashner	V y R	9	2012
62	7531689426538	La Torre Oscura	Stephen King	Donald M. Grant	5	1982
63	7531689426538	La Torre Oscura	Stephen King	Donald M. Grant	6	1982
64	7531689426538	La Torre Oscura	Stephen King	Donald M. Grant	7	1982
65	7531689426538	La Torre Oscura	Stephen King	Donald M. Grant	8	1982
66	7531689426538	La Torre Oscura	Stephen King	Donald M. Grant	9	1982
67	7531689426538	La Torre Oscura	Stephen King	Donald M. Grant	10	1982
187	978-1-449-34037-7	Python Cookbook	David Beazley, Brian K. Jones	O'REILLY	10	2013
188	978-970-26-0795-3	Física conceptual	Paul G. Hewitt	Pearson educación	1	2007
189	978-970-26-0795-3	Física conceptual	Paul G. Hewitt	Pearson educación	2	2007
190	978-970-26-0795-3	Física conceptual	Paul G. Hewitt	Pearson educación	3	2007
191	978-970-26-0795-3	Física conceptual	Paul G. Hewitt	Pearson educación	4	2007
192	978-970-26-0795-3	Física conceptual	Paul G. Hewitt	Pearson educación	5	2007
193	978-970-26-0795-3	Física conceptual	Paul G. Hewitt	Pearson educación	6	2007
194	978-970-26-0795-3	Física conceptual	Paul G. Hewitt	Pearson educación	7	2007
128	978-607-32-3802-1	Cómo programar en Java	Paul Deitel, Harvey Deitel	Pearson educación	2	2016
129	978-607-32-3802-1	Cómo programar en Java	Paul Deitel, Harvey Deitel	Pearson educación	3	2016
130	978-607-32-3802-1	Cómo programar en Java	Paul Deitel, Harvey Deitel	Pearson educación	4	2016
131	978-607-32-3802-1	Cómo programar en Java	Paul Deitel, Harvey Deitel	Pearson educación	5	2016
132	978-607-32-3802-1	Cómo programar en Java	Paul Deitel, Harvey Deitel	Pearson educación	6	2016
167	968-880-205-0	El lenguaje de programación C	Brian W. Kernighan, Dennis M. Ritchie	Pearson educación	1	1991
133	978-607-32-3802-1	Cómo programar en Java	Paul Deitel, Harvey Deitel	Pearson educación	7	2016
168	968-880-205-0	El lenguaje de programación C	Brian W. Kernighan, Dennis M. Ritchie	Pearson educación	2	1991
169	968-880-205-0	El lenguaje de programación C	Brian W. Kernighan, Dennis M. Ritchie	Pearson educación	3	1991
134	978-607-32-3802-1	Cómo programar en Java	Paul Deitel, Harvey Deitel	Pearson educación	8	2016
170	968-880-205-0	El lenguaje de programación C	Brian W. Kernighan, Dennis M. Ritchie	Pearson educación	4	1991
135	978-607-32-3802-1	Cómo programar en Java	Paul Deitel, Harvey Deitel	Pearson educación	9	2016
136	978-607-32-3802-1	Cómo programar en Java	Paul Deitel, Harvey Deitel	Pearson educación	10	2016
171	968-880-205-0	El lenguaje de programación C	Brian W. Kernighan, Dennis M. Ritchie	Pearson educación	5	1991
172	968-880-205-0	El lenguaje de programación C	Brian W. Kernighan, Dennis M. Ritchie	Pearson educación	6	1991
173	968-880-205-0	El lenguaje de programación C	Brian W. Kernighan, Dennis M. Ritchie	Pearson educación	7	1991
174	968-880-205-0	El lenguaje de programación C	Brian W. Kernighan, Dennis M. Ritchie	Pearson educación	8	1991
175	968-880-205-0	El lenguaje de programación C	Brian W. Kernighan, Dennis M. Ritchie	Pearson educación	9	1991
87	978-607-15-0760-0	Álgebra Lineal	Stanley I. Grossman S., José Job Flores Godoy	McGraw-Hill	1	2012
88	978-607-15-0760-0	Álgebra Lineal	Stanley I. Grossman S., José Job Flores Godoy	McGraw-Hill	2	2012
89	978-607-15-0760-0	Álgebra Lineal	Stanley I. Grossman S., José Job Flores Godoy	McGraw-Hill	3	2012
90	978-607-15-0760-0	Álgebra Lineal	Stanley I. Grossman S., José Job Flores Godoy	McGraw-Hill	4	2012
91	978-607-15-0760-0	Álgebra Lineal	Stanley I. Grossman S., José Job Flores Godoy	McGraw-Hill	5	2012
92	978-607-15-0760-0	Álgebra Lineal	Stanley I. Grossman S., José Job Flores Godoy	McGraw-Hill	6	2012
93	978-607-15-0760-0	Álgebra Lineal	Stanley I. Grossman S., José Job Flores Godoy	McGraw-Hill	7	2012
94	978-607-15-0760-0	Álgebra Lineal	Stanley I. Grossman S., José Job Flores Godoy	McGraw-Hill	8	2012
95	978-607-15-0760-0	Álgebra Lineal	Stanley I. Grossman S., José Job Flores Godoy	McGraw-Hill	9	2012
96	978-607-15-0760-0	Álgebra Lineal	Stanley I. Grossman S., José Job Flores Godoy	McGraw-Hill	10	2012
97	978-607-481-826-0	Precálculo Matemáticas para el cálculo	James Stewart, Lothar Redlin, Saleem Watson	CENAGAGE Learning	1	2012
98	978-607-481-826-0	Precálculo Matemáticas para el cálculo	James Stewart, Lothar Redlin, Saleem Watson	CENAGAGE Learning	2	2012
99	978-607-481-826-0	Precálculo Matemáticas para el cálculo	James Stewart, Lothar Redlin, Saleem Watson	CENAGAGE Learning	3	2012
100	978-607-481-826-0	Precálculo Matemáticas para el cálculo	James Stewart, Lothar Redlin, Saleem Watson	CENAGAGE Learning	4	2012
101	978-607-481-826-0	Precálculo Matemáticas para el cálculo	James Stewart, Lothar Redlin, Saleem Watson	CENAGAGE Learning	5	2012
102	978-607-481-826-0	Precálculo Matemáticas para el cálculo	James Stewart, Lothar Redlin, Saleem Watson	CENAGAGE Learning	6	2012
103	978-607-481-826-0	Precálculo Matemáticas para el cálculo	James Stewart, Lothar Redlin, Saleem Watson	CENAGAGE Learning	7	2012
104	978-607-481-826-0	Precálculo Matemáticas para el cálculo	James Stewart, Lothar Redlin, Saleem Watson	CENAGAGE Learning	8	2012
105	978-607-481-826-0	Precálculo Matemáticas para el cálculo	James Stewart, Lothar Redlin, Saleem Watson	CENAGAGE Learning	8	2012
106	978-607-481-826-0	Precálculo Matemáticas para el cálculo	James Stewart, Lothar Redlin, Saleem Watson	CENAGAGE Learning	10	2012
176	968-880-205-0	El lenguaje de programación C	Brian W. Kernighan, Dennis M. Ritchie	Pearson educación	10	1991
195	978-970-26-0795-3	Física conceptual	Paul G. Hewitt	Pearson educación	8	2007
196	978-970-26-0795-3	Física conceptual	Paul G. Hewitt	Pearson educación	9	2007
197	978-970-26-0795-3	Física conceptual	Paul G. Hewitt	Pearson educación	10	2007
198	978-1-4302-1912-5	Pro Linux System Administration	James Turnbull, Peter Lieverdink, Dennis Matotek	Apress	1	2009
199	978-1-4302-1912-5	Pro Linux System Administration	James Turnbull, Peter Lieverdink, Dennis Matotek	Apress	2	2009
200	978-1-4302-1912-5	Pro Linux System Administration	James Turnbull, Peter Lieverdink, Dennis Matotek	Apress	3	2009
201	978-1-4302-1912-5	Pro Linux System Administration	James Turnbull, Peter Lieverdink, Dennis Matotek	Apress	4	2009
202	978-1-4302-1912-5	Pro Linux System Administration	James Turnbull, Peter Lieverdink, Dennis Matotek	Apress	5	2009
203	978-1-4302-1912-5	Pro Linux System Administration	James Turnbull, Peter Lieverdink, Dennis Matotek	Apress	6	2009
204	978-1-4302-1912-5	Pro Linux System Administration	James Turnbull, Peter Lieverdink, Dennis Matotek	Apress	7	2009
205	978-1-4302-1912-5	Pro Linux System Administration	James Turnbull, Peter Lieverdink, Dennis Matotek	Apress	8	2009
206	978-1-4302-1912-5	Pro Linux System Administration	James Turnbull, Peter Lieverdink, Dennis Matotek	Apress	9	2009
207	978-1-4302-1912-5	Pro Linux System Administration	James Turnbull, Peter Lieverdink, Dennis Matotek	Apress	10	2009
3	978-0-13-459632-7	C# for programmers	Paul Deitel, Harvey Deitel	Pearson educación	6	2016
208	978-1-4302-1889-0	Beginning the Linux Command Line	Sander van Vugt	Apress	1	2009
209	978-1-4302-1889-0	Beginning the Linux Command Line	Sander van Vugt	Apress	2	2009
11	978-84-7829-085	Fundamentos de Sistemas de Bases de Datos	Ramez Elmasri, Shamkant B. Navathe	Pearson educación	1	2007
12	978-84-7829-085	Fundamentos de Sistemas de Bases de Datos	Ramez Elmasri, Shamkant B. Navathe	Pearson educación	2	2007
13	978-84-7829-085	Fundamentos de Sistemas de Bases de Datos	Ramez Elmasri, Shamkant B. Navathe	Pearson educación	3	2007
14	978-84-7829-085	Fundamentos de Sistemas de Bases de Datos	Ramez Elmasri, Shamkant B. Navathe	Pearson educación	4	2007
15	978-84-7829-085	Fundamentos de Sistemas de Bases de Datos	Ramez Elmasri, Shamkant B. Navathe	Pearson educación	5	2007
16	978-84-7829-085	Fundamentos de Sistemas de Bases de Datos	Ramez Elmasri, Shamkant B. Navathe	Pearson educación	6	2007
17	978-84-7829-085	Fundamentos de Sistemas de Bases de Datos	Ramez Elmasri, Shamkant B. Navathe	Pearson educación	7	2007
18	978-84-7829-085	Fundamentos de Sistemas de Bases de Datos	Ramez Elmasri, Shamkant B. Navathe	Pearson educación	8	2007
19	978-84-7829-085	Fundamentos de Sistemas de Bases de Datos	Ramez Elmasri, Shamkant B. Navathe	Pearson educación	9	2007
20	978-84-7829-085	Fundamentos de Sistemas de Bases de Datos	Ramez Elmasri, Shamkant B. Navathe	Pearson educación	10	2007
78	978-0-13-459632-7	C# for programmers	Paul Deitel, Harvey Deitel	Pearson educación	1	2016
79	978-0-13-459632-7	C# for programmers	Paul Deitel, Harvey Deitel	Pearson educación	2	2016
80	978-0-13-459632-7	C# for programmers	Paul Deitel, Harvey Deitel	Pearson educación	4	2016
81	978-0-13-459632-7	C# for programmers	Paul Deitel, Harvey Deitel	Pearson educación	5	2016
82	978-0-13-459632-7	C# for programmers	Paul Deitel, Harvey Deitel	Pearson educación	6	2016
83	978-0-13-459632-7	C# for programmers	Paul Deitel, Harvey Deitel	Pearson educación	7	2016
84	978-0-13-459632-7	C# for programmers	Paul Deitel, Harvey Deitel	Pearson educación	8	2016
85	978-0-13-459632-7	C# for programmers	Paul Deitel, Harvey Deitel	Pearson educación	9	2016
86	978-0-13-459632-7	C# for programmers	Paul Deitel, Harvey Deitel	Pearson educación	10	2016
107	978-607-32-2739-1	C++ Cómo programar	Paul Deitel, Harvey Deitel	Pearson educación	1	2014
108	978-607-32-2739-1	C++ Cómo programar	Paul Deitel, Harvey Deitel	Pearson educación	2	2014
109	978-607-32-2739-1	C++ Cómo programar	Paul Deitel, Harvey Deitel	Pearson educación	3	2014
110	978-607-32-2739-1	C++ Cómo programar	Paul Deitel, Harvey Deitel	Pearson educación	4	2014
111	978-607-32-2739-1	C++ Cómo programar	Paul Deitel, Harvey Deitel	Pearson educación	5	2014
112	978-607-32-2739-1	C++ Cómo programar	Paul Deitel, Harvey Deitel	Pearson educación	6	2014
113	978-607-32-2739-1	C++ Cómo programar	Paul Deitel, Harvey Deitel	Pearson educación	7	2014
114	978-607-32-2739-1	C++ Cómo programar	Paul Deitel, Harvey Deitel	Pearson educación	8	2014
115	978-607-32-2739-1	C++ Cómo programar	Paul Deitel, Harvey Deitel	Pearson educación	9	2014
116	978-607-32-2739-1	C++ Cómo programar	Paul Deitel, Harvey Deitel	Pearson educación	10	2014
117	970-26-0637-3	Matemáticas discretas	Richard Johnsonbaugh	Pearson educación	1	2005
118	970-26-0637-3	Matemáticas discretas	Richard Johnsonbaugh	Pearson educación	2	2005
119	970-26-0637-3	Matemáticas discretas	Richard Johnsonbaugh	Pearson educación	3	2005
120	970-26-0637-3	Matemáticas discretas	Richard Johnsonbaugh	Pearson educación	4	2005
121	970-26-0637-3	Matemáticas discretas	Richard Johnsonbaugh	Pearson educación	5	2005
122	970-26-0637-3	Matemáticas discretas	Richard Johnsonbaugh	Pearson educación	6	2005
123	970-26-0637-3	Matemáticas discretas	Richard Johnsonbaugh	Pearson educación	7	2005
124	970-26-0637-3	Matemáticas discretas	Richard Johnsonbaugh	Pearson educación	8	2005
125	970-26-0637-3	Matemáticas discretas	Richard Johnsonbaugh	Pearson educación	9	2005
126	970-26-0637-3	Matemáticas discretas	Richard Johnsonbaugh	Pearson educación	10	2005
137	0-13-177429-8	Expert C Programming	Peter van der Linden	SunSoft Press	1	1994
138	0-13-177429-8	Expert C Programming	Peter van der Linden	SunSoft Press	2	1994
139	0-13-177429-8	Expert C Programming	Peter van der Linden	SunSoft Press	3	1994
140	0-13-177429-8	Expert C Programming	Peter van der Linden	SunSoft Press	4	1994
141	0-13-177429-8	Expert C Programming	Peter van der Linden	SunSoft Press	5	1994
142	0-13-177429-8	Expert C Programming	Peter van der Linden	SunSoft Press	6	1994
143	0-13-177429-8	Expert C Programming	Peter van der Linden	SunSoft Press	7	1994
144	0-13-177429-8	Expert C Programming	Peter van der Linden	SunSoft Press	8	1994
145	0-13-177429-8	Expert C Programming	Peter van der Linden	SunSoft Press	9	1994
146	0-13-177429-8	Expert C Programming	Peter van der Linden	SunSoft Press	10	1994
147	978-1-59327-603-4	Python Crash Course	Eric Matthes	No Starch Press	1	2015
148	978-1-59327-603-4	Python Crash Course	Eric Matthes	No Starch Press	2	2015
149	978-1-59327-603-4	Python Crash Course	Eric Matthes	No Starch Press	3	2015
150	978-1-59327-603-4	Python Crash Course	Eric Matthes	No Starch Press	4	2015
151	978-1-59327-603-4	Python Crash Course	Eric Matthes	No Starch Press	5	2015
152	978-1-59327-603-4	Python Crash Course	Eric Matthes	No Starch Press	6	2015
153	978-1-59327-603-4	Python Crash Course	Eric Matthes	No Starch Press	7	2015
154	978-1-59327-603-4	Python Crash Course	Eric Matthes	No Starch Press	8	2015
155	978-1-59327-603-4	Python Crash Course	Eric Matthes	No Starch Press	9	2015
156	978-1-59327-603-4	Python Crash Course	Eric Matthes	No Starch Press	10	2015
210	978-1-4302-1889-0	Beginning the Linux Command Line	Sander van Vugt	Apress	3	2009
211	978-1-4302-1889-0	Beginning the Linux Command Line	Sander van Vugt	Apress	4	2009
212	978-1-4302-1889-0	Beginning the Linux Command Line	Sander van Vugt	Apress	5	2009
213	978-1-4302-1889-0	Beginning the Linux Command Line	Sander van Vugt	Apress	6	2009
214	978-1-4302-1889-0	Beginning the Linux Command Line	Sander van Vugt	Apress	7	2009
215	978-1-4302-1889-0	Beginning the Linux Command Line	Sander van Vugt	Apress	8	2009
216	978-1-4302-1889-0	Beginning the Linux Command Line	Sander van Vugt	Apress	9	2009
217	978-1-4302-1889-0	Beginning the Linux Command Line	Sander van Vugt	Apress	10	2009
219	978-84-205-4110-5	Comunicaciones y Redes de Computadores	William Stallings	Pearson educacion	2	2004
220	978-84-205-4110-5	Comunicaciones y Redes de Computadores	William Stallings	Pearson educacion	3	2004
221	978-84-205-4110-5	Comunicaciones y Redes de Computadores	William Stallings	Pearson educacion	4	2004
222	978-84-205-4110-5	Comunicaciones y Redes de Computadores	William Stallings	Pearson educacion	5	2004
223	978-84-205-4110-5	Comunicaciones y Redes de Computadores	William Stallings	Pearson educacion	6	2004
224	978-84-205-4110-5	Comunicaciones y Redes de Computadores	William Stallings	Pearson educacion	7	2004
225	978-84-205-4110-5	Comunicaciones y Redes de Computadores	William Stallings	Pearson educacion	8	2004
226	978-84-205-4110-5	Comunicaciones y Redes de Computadores	William Stallings	Pearson educacion	9	2004
227	978-84-205-4110-5	Comunicaciones y Redes de Computadores	William Stallings	Pearson educacion	10	2004
218	978-84-205-4110-5	Comunicaciones y Redes de Computadores	William Stallings	Pearson educación	1	2004
\.


--
-- Data for Name: prestamo; Type: TABLE DATA; Schema: public; Owner: adrian
--

COPY public.prestamo (codigo, codigo_libro, codigo_cliente, codigo_empleado, fecha_prestamo, fecha_entrega) FROM stdin;
155	127	21	1	2019-05-03 13:34:01	2019-05-17 17:00:00
156	59	26	15	2019-05-03 15:13:23	2019-05-17 17:00:00
157	21	22	17	2019-05-10 16:01:23	2019-05-24 17:00:00
158	41	3	14	2019-05-10 14:03:20	2019-05-17 17:00:00
161	9	4	17	2019-05-11 13:00:20	2019-05-18 14:00:00
162	8	19	12	2019-05-06 14:13:00	2019-05-13 17:00:00
163	10	33	15	2019-05-17 14:03:20	2019-05-31 17:00:00
164	22	22	19	2019-05-08 16:15:50	2019-05-15 17:00:00
165	23	23	17	2019-05-09 13:05:40	2019-05-16 17:00:00
166	50	30	12	2019-05-17 11:05:00	2019-05-31 17:00:00
167	157	29	21	2019-05-17 09:03:20	2019-05-31 17:00:00
\.


--
-- Name: empleado_codigo_seq; Type: SEQUENCE SET; Schema: public; Owner: adrian
--

SELECT pg_catalog.setval('public.empleado_codigo_seq', 21, true);


--
-- Name: libro_codigo_libro_seq; Type: SEQUENCE SET; Schema: public; Owner: adrian
--

SELECT pg_catalog.setval('public.libro_codigo_libro_seq', 227, true);


--
-- Name: prestamo_codigo_seq; Type: SEQUENCE SET; Schema: public; Owner: adrian
--

SELECT pg_catalog.setval('public.prestamo_codigo_seq', 186, true);


--
-- Name: usuario_codigo_seq; Type: SEQUENCE SET; Schema: public; Owner: adrian
--

SELECT pg_catalog.setval('public.usuario_codigo_seq', 33, true);


--
-- Name: prestamo codigo_libro; Type: CONSTRAINT; Schema: public; Owner: adrian
--

ALTER TABLE ONLY public.prestamo
    ADD CONSTRAINT codigo_libro UNIQUE (codigo_libro);


--
-- Name: empleado empleado_nombre_usuario_key; Type: CONSTRAINT; Schema: public; Owner: adrian
--

ALTER TABLE ONLY public.empleado
    ADD CONSTRAINT empleado_nombre_usuario_key UNIQUE (nombre_usuario);


--
-- Name: empleado empleado_pkey; Type: CONSTRAINT; Schema: public; Owner: adrian
--

ALTER TABLE ONLY public.empleado
    ADD CONSTRAINT empleado_pkey PRIMARY KEY (codigo);


--
-- Name: libro libro_pkey; Type: CONSTRAINT; Schema: public; Owner: adrian
--

ALTER TABLE ONLY public.libro
    ADD CONSTRAINT libro_pkey PRIMARY KEY (codigo);


--
-- Name: prestamo prestamo_pkey; Type: CONSTRAINT; Schema: public; Owner: adrian
--

ALTER TABLE ONLY public.prestamo
    ADD CONSTRAINT prestamo_pkey PRIMARY KEY (codigo);


--
-- Name: cliente usuario_pkey; Type: CONSTRAINT; Schema: public; Owner: adrian
--

ALTER TABLE ONLY public.cliente
    ADD CONSTRAINT usuario_pkey PRIMARY KEY (codigo);


--
-- Name: prestamo prestamo_codigo_cliente_fkey; Type: FK CONSTRAINT; Schema: public; Owner: adrian
--

ALTER TABLE ONLY public.prestamo
    ADD CONSTRAINT prestamo_codigo_cliente_fkey FOREIGN KEY (codigo_cliente) REFERENCES public.cliente(codigo);


--
-- Name: prestamo prestamo_codigo_empleado_fkey; Type: FK CONSTRAINT; Schema: public; Owner: adrian
--

ALTER TABLE ONLY public.prestamo
    ADD CONSTRAINT prestamo_codigo_empleado_fkey FOREIGN KEY (codigo_empleado) REFERENCES public.empleado(codigo);


--
-- Name: prestamo prestamo_codigo_libro_fkey; Type: FK CONSTRAINT; Schema: public; Owner: adrian
--

ALTER TABLE ONLY public.prestamo
    ADD CONSTRAINT prestamo_codigo_libro_fkey FOREIGN KEY (codigo_libro) REFERENCES public.libro(codigo);


--
-- PostgreSQL database dump complete
--

