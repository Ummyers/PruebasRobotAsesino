create table Empleado(
  curp varchar(18) PRIMARY KEY,
  nombre varchar(255),
  paterno varchar(255),
  materno varchar(255),
  f_nac date,
  calle varchar(255),
  num number(5,0),
  ciudad varchar(255),
  CP varchar(255));

CREATE TABLE Empresa(
  rfc varchar(18) PRIMARY KEY,
  razon_social varchar(255),
  calle varchar(255),
  num number(5,0),
  ciudad varchar(255),
  CP varchar(255));
  
CREATE TABLE Proyecto(
	numProy int PRIMARY KEY,
	nombre varchar(255),
	fecha_inicio date,
	fecha_fin date);

CREATE TABLE Supervisar(
	curp_supervisado varchar(18),
	curp_jefe varchar(18));

alter table Supervisar add constraint PK_Supervisar PRIMARY KEY(curp_supervisado, curp_jefe);
alter table Supervisar add constraint FK_curp_supervisado foreign key(curp_supervisado) references Empleado(curp);
alter table Supervisar add constraint FK_curp_jefe foreign key(curp_jefe) references Empleado(curp);

CREATE TABLE Trabajar(
	curp varchar(18),
	rfc varchar(18),
	fecha_ingreso date,
	salario int);

alter table Trabajar add constraint PK_Trabajar PRIMARY KEY(curp, rfc);
alter table Trabajar add constraint FK_curp foreign key(curp) references Empleado(curp);
alter table Trabajar add constraint FK_rfc foreign key(rfc) references Empresa(rfc);

CREATE TABLE Dirigir(
	curp varchar(18),
	rfc varchar(18),
	fecha_inicio date);

alter table Dirigir add constraint PK_Dirigir PRIMARY KEY(curp, rfc);
alter table Dirigir add constraint FK_curp_dirigir foreign key(curp) references Empleado(curp);
alter table Dirigir add constraint FK_rfc_dirigir foreign key(rfc) references Empresa(rfc);

CREATE TABLE Colaborar(
	curp varchar(18),
	numProy int,
	fecha_inicio date,
	fecha_fin date,
	numHoras int);

alter table Colaborar add constraint PK_Colaborar PRIMARY KEY (curp, numProy);
alter table Colaborar add constraint FK_curp_colaborar foreign key (curp) references Empleado(curp);
alter table Colaborar add constraint FK_numProy_colaborar foreign key (numProy) references Proyecto(numProy);

CREATE TABLE Controlar(
	rfc varchar(18),
	numProy int);

alter table Controlar add constraint PK_Controlar PRIMARY KEY (rfc, numProy);
alter table Controlar add constraint FK_rfc_controlar foreign key (rfc) references Empresa (rfc);
alter table Controlar add constraint FK_numProy_controlar foreign key (numProy) references Proyecto (numProy);