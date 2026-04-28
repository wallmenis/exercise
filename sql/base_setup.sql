DROP TABLE stock;
DROP TABLE out_of_stock;
DROP TABLE toat;
DROP TRIGGER trg_prevent_negative_stock;
DROP PROCEDURE generate_stock_data;


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


CREATE OR REPLACE TRIGGER trg_prevent_negative_stock
BEFORE UPDATE OF quantity ON stock
FOR EACH ROW
BEGIN
   
    IF :NEW.quantity < 0 THEN
        RAISE_APPLICATION_ERROR(-20003, 'Stock cannot be negative');
    END IF;
END;
/

CREATE OR REPLACE PROCEDURE generate_stock_data
IS
    TYPE product_array IS VARRAY(10) OF VARCHAR2(100);
    products product_array := product_array(
        'Shirt A',
        'Shirt B',
        'Shorts',
        'Socks A',
        'Socks B',
        'Shoes A',
        'Shoes B',
        'Hat A',
        'Hat B',
        'Gloves'
    );
BEGIN
    FOR i IN 1..products.COUNT LOOP
        INSERT INTO stock (id, name, quantity)
        VALUES (
            i,
            products(i),
            TRUNC(DBMS_RANDOM.VALUE(1, 100))
        );
    END LOOP;

    COMMIT;
END;
/

BEGIN
    generate_stock_data;
END;
/

EXIT;

