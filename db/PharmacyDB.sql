CREATE TABLE company (
  comp_id    VARCHAR(10) not NULL,
  comp_name VARCHAR(20) not NULL,
  comp_adress  VARCHAR(40),
  comp_contact VARCHAR(20),
  comp_password  VARCHAR(20),
  PRIMARY KEY (comp_id)
);

CREATE TABLE drugstore (
  store_id    VARCHAR(10) not NULL,
  store_name VARCHAR(20) not NULL,
  store_adress  VARCHAR(40),
  store_contact VARCHAR(20),
  store_password  VARCHAR(20),
  PRIMARY KEY (store_id)
);

CREATE TABLE medicine (
  med_id    VARCHAR(10) not NULL,
  med_name VARCHAR(20) not NULL,
  med_description  VARCHAR(200),
  med_price NUMERIC(12, 2) not NULL,
  comp_id   VARCHAR(10) not NULL,
  PRIMARY KEY (med_id),
  FOREIGN KEY (comp_id) REFERENCES company(comp_id)
  ON DELETE CASCADE
);


CREATE TABLE journal
 (
  trans_id    VARCHAR(10) not NULL,
  trans_date Date,
  comp_id   VARCHAR(10) not NULL,
  store_id VARCHAR(10) not NULL,
  med_id VARCHAR(10) not NULL,
  quantity NUMERIC(4),
  PRIMARY KEY (med_id),
  FOREIGN KEY (comp_id) REFERENCES company(comp_id)
    ON DELETE SET NULL,
  FOREIGN KEY (store_id) REFERENCES drugstore(store_id)
    ON DELETE SET NULL,
  FOREIGN KEY (med_id) REFERENCES medicine(med_id)
    ON DELETE SET NULL
);





