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
EXIT;