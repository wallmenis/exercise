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
BEGIN
    -- if item already exists in out of stock  update it
    UPDATE out_of_stock
    SET quantity = :NEW.quantity,
        name     = :NEW.name
    WHERE id = :OLD.id;

    -- if it doesnt exist  insert it
    IF SQL%ROWCOUNT = 0 THEN
        INSERT INTO out_of_stock (id, name, quantity, toat_id)
        VALUES (:OLD.id, :NEW.name, :NEW.quantity, NULL);
    END IF;

EXCEPTION
    WHEN OTHERS THEN
        RAISE_APPLICATION_ERROR(-20002, 'Error updating out_of_stock');
END;
/

CREATE OR REPLACE TRIGGER trg_prevent_negative_stock
BEFORE UPDATE OF quantity ON stock
FOR EACH ROW
BEGIN
   
    IF :NEW.quantity < 0 THEN
        RAISE_APPLICATION_ERROR(-20003, 'Stock cannot be negative');
    END IF;
END;
/
EXIT;
