FROM oraclelinux:9 AS build_env

RUN dnf update -y && \
    dnf install -y oracle-instantclient-release-23ai-el9 && \
    dnf install -y gcc g++ &&\
    dnf install -y oracle-instantclient-basic &&\
    dnf install -y oracle-instantclient-devel && \
    dnf install -y oracle-instantclient-odbc && \
    dnf install -y oracle-instantclient-sqlplus && \
    dnf install -y oracle-epel-release-el9 && \
    dnf install -y json-devel && \
    dnf install -y jq && \
    dnf clean all

COPY ./src /app/src
COPY ./container_scripts/build_script.sh /app/build_script.sh
COPY ./conf /app/conf
COPY ./sql /app/sql
COPY ./container_scripts/init_database.sh /app/init_database.sh
COPY ./container_scripts/run_testing.sh /app/run_testing.sh

RUN dnf update -y && \ 
    dnf clean all       # Update for a second time to ensure all packages are up to date and clean the cache again

WORKDIR /app

RUN useradd user && \
    chown -R user:user /app  # Change ownership of the app directory to the non-root user

# Switch to the non-root user for building and running the application
USER user   

ENV ORACLE_LIBS=/usr/lib/oracle/23/client64/lib
ENV ORACLE_INCLUDES=/usr/include/oracle/23/client64

RUN ./build_script.sh

RUN mkdir -p /app/logs

WORKDIR /app/bin

CMD ["/bin/bash"]

FROM build_env AS db_init

WORKDIR /app

CMD ["/app/init_database.sh"]

FROM build_env AS main_app

CMD ["/app/bin/main"]

FROM build_env AS test_image

WORKDIR /app

CMD ["/app/run_testing.sh"]