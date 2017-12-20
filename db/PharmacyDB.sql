CREATE TABLE authorization(
  id VARCHAR (10) not NULL,
  password VARCHAR(20) not NULL,
  type NUMERIC(1) check (type in (0, 1, 2)),
  PRIMARY KEY (id)
);
CREATE TABLE company (
  id    VARCHAR(10) not NULL,
  comp_name VARCHAR(20) not NULL,
  comp_address  VARCHAR(40),
  comp_contact VARCHAR(20),
  PRIMARY KEY (id),
  FOREIGN KEY (id) REFERENCES authorization(id)
);

CREATE TABLE drugstore (
  id    VARCHAR(10) not NULL,
  store_name VARCHAR(20) not NULL,
  store_address  VARCHAR(40),
  store_contact VARCHAR(20),
  PRIMARY KEY (id),
  FOREIGN KEY (id) REFERENCES authorization(id)
);

CREATE TABLE medicine (
  med_id    VARCHAR(10) not NULL,
  med_name VARCHAR(20) not NULL,
  med_description  VARCHAR(200),
  med_price NUMERIC(12, 2) not NULL,
  comp_id   VARCHAR(10) not NULL,
  PRIMARY KEY (med_id),
  FOREIGN KEY (comp_id) REFERENCES company(id)
  ON DELETE CASCADE
);

CREATE TABLE inventory(
id VARCHAR(10) not null,
med_id VARCHAR(10) not null,
med_name VARCHAR(20) not null,
med_quantity NUMERIC(4),
PRIMARY KEY (id, med_id),
FOREIGN KEY (id) REFERENCES drugstore(store_id)
ON DELETE CASCADE,
FOREIGN KEY (med_id) REFERENCES medicine(med_id)
on DELETE CASCADE
);

CREATE TABLE journal
 (
  trans_id    INTEGER(11) not NULL AUTO_INCREMENT,
  trans_date timestamp,
  comp_id   VARCHAR(10) not NULL,
  store_id VARCHAR(10) not NULL,
  med_id VARCHAR(10) not NULL,
  quantity NUMERIC(4),
  status NUMERIC(1) check (status in (0,1)),
  PRIMARY KEY (trans_id),
  FOREIGN KEY (comp_id) REFERENCES company(id)
    ON DELETE CASCADE,
  FOREIGN KEY (store_id) REFERENCES drugstore(id)
    ON DELETE CASCADE,
  FOREIGN KEY (med_id) REFERENCES medicine(med_id)
    ON DELETE CASCADE
);
