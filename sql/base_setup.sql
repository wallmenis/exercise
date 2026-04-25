-- STOCK TABLE
CREATE TABLE IF NOT EXISTS stock (
    id        NUMBER,
    name      VARCHAR2(100) NOT NULL,
    quantity  NUMBER NOT NULL,
    PRIMARY KEY (id)
);

-- TOAT TABLE
CREATE TABLE IF NOT EXISTS toat (
    id        NUMBER,
    order_id  NUMBER NOT NULL,
    PRIMARY KEY (id)
);

-- OUT-OF-STOCK TABLE
CREATE TABLE IF NOT EXISTS out_of_stock (
    id        NUMBER,
    name      VARCHAR2(100) NOT NULL,
    quantity  NUMBER NOT NULL,
    toat_id   NUMBER,
    PRIMARY KEY (id),
    FOREIGN KEY (toat_id) REFERENCES toat(id)
);
EXIT;