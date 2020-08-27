#!/bin/bash

n=$1


cat tests/input$n.txt

./aristizabal_FINAL < tests/input$n.txt

echo -e "\n"

cat tests/output$n.txt
