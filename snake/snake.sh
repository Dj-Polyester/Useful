#!/bin/bash

program "$@"
while [ $? -e 42 ]; do
    program "$@"
done
