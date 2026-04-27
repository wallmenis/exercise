#!/bin/bash


config_file="conf/conf.json"
username=$(cat $config_file | jq | grep "username" | cut -d':' -f2 | cut -d'"' -f2)
password=$(cat $config_file | jq | grep "password" | cut -d':' -f2 | cut -d'"' -f2)
db_connection_string1=$(cat $config_file | jq | grep "db_connection_string" | cut -d':' -f2 | cut -d'"' -f2)
db_connection_string2=$(cat $config_file | jq | grep "db_connection_string" | cut -d':' -f3 | cut -d'"' -f1)
db_connection_string=$db_connection_string1:$db_connection_string2
connect_string="$username/$password@$db_connection_string"
echo "Connecting to database with: $connect_string"
sqlplus $connect_string @$(pwd)/sql/base_setup.sql &> logs/db_init_test.log
sqlplus $connect_string @$(pwd)/sql/testing_base.sql &>> logs/db_init_test.log
cd ./bin
./main 1 1 2 3
./main 1 3 2 5
./main 5
echo "Testing completed!"
