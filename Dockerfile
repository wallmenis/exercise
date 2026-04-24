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

ENV ORACLE_LIBS=/usr/lib/oracle/23/client64/lib
ENV ORACLE_INCLUDES=/usr/include/oracle/23/client64


COPY . /app

WORKDIR /app

RUN ./build_script.sh

WORKDIR /app/bin

RUN mkdir -p /app/logs

CMD ["/app/bin/main"]