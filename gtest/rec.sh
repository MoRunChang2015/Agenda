cp -f standardData/rec_*.csv data/
mv data/rec_users.csv data/users.csv
mv data/rec_meetings.csv data/meetings.csv
echo "content in data/"
cat data/*
