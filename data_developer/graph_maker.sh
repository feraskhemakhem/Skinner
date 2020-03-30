cd ../build
make -j4
# ./A6 3 1000 100 10 2 0 -1 ../data/temp_0.txt 0 0 # DQS
# ./A6 3 1000 100 10 2 0 5 ../data/temp_0.txt 0 0.5 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_1.txt 0 1 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_2.txt 0.25 0.5 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_3.txt 0.25 1 # with 3 bones
# ./A6 3 1000 100 10 2 0 -1 ../data/temp_4.txt 0.5 0.5 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_5.txt 0.5 1 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_6.txt 0.75 0.5 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_7.txt 0.75 1 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_8.txt 1 0.5 # with 3 bones
# ./A6 3 1000 100 10 2 0 5 ../data/temp_9.txt 1 1 # LBS

# ./A6 3 100 10 10 2 0 -1 ../data/temp_0.txt 0 0 # DQS

cd ../data_developer
python3 graph_maker.py linear_interpolation_test.png
cd ../data 
rm temp*