#!/bin/bash


config_file="conf/conf.json"
username=$(cat $config_file | jq | grep "username" | cut -d':' -f2 | cut -d'"' -f2)
password=$(cat $config_file | jq | grep "password" | cut -d':' -f2 | cut -d'"' -f2)
db_connection_string1=$(cat $config_file | jq | grep "db_connection_string" | cut -d':' -f2 | cut -d'"' -f2)
db_connection_string2=$(cat $config_file | jq | grep "db_connection_string" | cut -d':' -f3 | cut -d'"' -f1)
db_connection_string="$db_connection_string1:$db_connection_string2"
sqlplus "$username/$password@$db_connection_string" @$(pwd)/sql/init_db.sql &> generator.log
cd ./bin
./random_data_generator
cat ./generator.log