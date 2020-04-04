cd ../build
make -j4

# smooth base

# ./A6 3 1000 100 10 2 0 5 ../data/temp_0.txt 0 0 # LBS
# ./A6 3 1000 100 10 2 0 5 ../data/temp_1.txt 0 0.5 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_2.txt 0 1 # with 3 bones
# ./A6 3 1000 100 10 2 0.25 5 ../data/temp_3.txt 0.25 0 # with 3 bones
# ./A6 3 1000 100 10 2 0.25 5 ../data/temp_4.txt 0.25 0.5 # with 3 bones
# ./A6 3 1000 100 10 2 0.25 5 ../data/temp_5.txt 0.25 1 # with 3 bones
# ./A6 3 1000 100 10 2 0.5 5 ../data/temp_6.txt 0.5 0 # with 3 bones
# ./A6 3 1000 100 10 2 0.5 5 ../data/temp_7.txt 0.5 0.5 # with 3 bones
# ./A6 3 1000 100 10 2 0.5 5 ../data/temp_8.txt 0.5 1 # with 3 bones
# ./A6 3 1000 100 10 2 0.75 5 ../data/temp_9.txt 0.75 0 # with 3 bones
# ./A6 3 1000 100 10 2 0.75 5 ../data/temp_10.txt 0.75 0.5 # with 3 bones
# ./A6 3 1000 100 10 2 0.75 5 ../data/temp_11.txt 0.75 1 # with 3 bones
# ./A6 3 1000 100 10 2 1 5 ../data/temp_12.txt 1 0 # with 3 bones
# ./A6 3 1000 100 10 2 1 5 ../data/temp_13.txt 1 0.5 # with 3 bones
# ./A6 3 1000 100 10 2 1 5 ../data/temp_14.txt 1 1 # DQS

./A6 3 1000 100 10 2 0 5 ../data/temp_0.txt 0 0 # LBS
./A6 3 1000 100 10 2 1 5 ../data/temp_1.txt 1 1 # DQS

# LBS base

# ./A6 3 1000 100 10 2 0 5 ../data/temp_0.txt 0 0 # LBS
# ./A6 3 1000 100 10 2 0 5 ../data/temp_1.txt 0 0.5 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_2.txt 0 1 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_3.txt 0.25 0 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_4.txt 0.25 0.5 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_5.txt 0.25 1 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_6.txt 0.5 0 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_7.txt 0.5 0.5 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_8.txt 0.5 1 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_9.txt 0.75 0 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_10.txt 0.75 0.5 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_11.txt 0.75 1 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_12.txt 1 0 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_13.txt 1 0.5 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_14.txt 1 1 # DQS


# DQS base

# ./A6 3 1000 100 10 2 1 5 ../data/temp_0.txt 0 0 # LBS
# ./A6 3 1000 100 10 2 1 5 ../data/temp_1.txt 0 0.5 # with 3 bones
# ./A6 3 1000 100 10 2 1 5 ../data/temp_2.txt 0 1 # with 3 bones
# ./A6 3 1000 100 10 2 1 5 ../data/temp_3.txt 0.25 0 # with 3 bones
# ./A6 3 1000 100 10 2 1 5 ../data/temp_4.txt 0.25 0.5 # with 3 bones
# ./A6 3 1000 100 10 2 1 5 ../data/temp_5.txt 0.25 1 # with 3 bones
# ./A6 3 1000 100 10 2 1 5 ../data/temp_6.txt 0.5 0 # with 3 bones
# ./A6 3 1000 100 10 2 1 5 ../data/temp_7.txt 0.5 0.5 # with 3 bones
# ./A6 3 1000 100 10 2 1 5 ../data/temp_8.txt 0.5 1 # with 3 bones
# ./A6 3 1000 100 10 2 1 5 ../data/temp_9.txt 0.75 0 # with 3 bones
# ./A6 3 1000 100 10 2 1 5 ../data/temp_10.txt 0.75 0.5 # with 3 bones
# ./A6 3 1000 100 10 2 1 5 ../data/temp_11.txt 0.75 1 # with 3 bones
# ./A6 3 1000 100 10 2 1 5 ../data/temp_12.txt 1 0 # with 3 bones
# ./A6 3 1000 100 10 2 1 5 ../data/temp_13.txt 1 0.5 # with 3 bones
# ./A6 3 1000 100 10 2 1 5 ../data/temp_14.txt 1 1 # DQS

cd ../data_developer
python3 graph_maker.py linear_interpolation_test.png
cd ../data 
rm temp*