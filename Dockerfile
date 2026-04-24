FROM oraclelinux:9

RUN dnf update -y && \
    dnf install -y oracle-instantclient-release-23ai-el9 && \
    dnf install -y gcc g++ &&\
    dnf install -y oracle-instantclient-basic &&\
    dnf install -y oracle-instantclient-devel && \
    dnf install -y oracle-instantclient-odbc && \
    dnf install -y oracle-epel-release-el9 && \
    dnf install -y json-devel && \
    dnf clean all

COPY ./src /app/src
COPY ./build_script.sh /app/build_script.sh
COPY ./conf /app/conf

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

WORKDIR /app/bin

RUN mkdir -p /app/logs

# RUN ./random_data_generator

CMD ["/app/bin/main"]