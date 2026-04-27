DROP TABLE stock;
DROP TABLE toat;
DROP TABLE out_of_stock;

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
    PRIMARY KEY (id, toat_id),
    FOREIGN KEY (toat_id) REFERENCES toat(id)
);


CREATE OR REPLACE TRIGGER trg_stock_to_out_of_stock
AFTER UPDATE OF quantity ON stock
FOR EACH ROW
WHEN (NEW.quantity = 0)
BEGIN
    -- Move item to out_of_stock
    INSERT INTO out_of_stock (id, name, quantity, toat_id)
    VALUES (:OLD.id, :OLD.name, :OLD.quantity, NULL);

    -- Remove from stock table
    DELETE FROM stock
    WHERE id = :OLD.id;

EXCEPTION
    WHEN OTHERS THEN
        RAISE_APPLICATION_ERROR(-20002, 'Error moving stock to out_of_stock');
END;
/



INSERT INTO stock VALUES (1, 'SOCKS', 2);
INSERT INTO stock VALUES (2, 'SHOES', 2);
INSERT INTO stock VALUES (3, 'T-SHIRT', 2);
INSERT INTO stock VALUES (4, 'JACKET', 2);
INSERT INTO stock VALUES (5, 'SNEAKERS', 2);
INSERT INTO stock VALUES (6, 'BALL', 2);
INSERT INTO stock VALUES (7, 'GLOVES', 2);
INSERT INTO stock VALUES (8, 'LEGGINGS', 2);
INSERT INTO stock VALUES (9, 'TOWEL', 2);
INSERT INTO stock VALUES (10, 'TOWEL B', 2);
INSERT INTO stock VALUES (11, 'SOCKS A', 2);
INSERT INTO stock VALUES (12, 'SOCKS B', 2);

EXIT;

