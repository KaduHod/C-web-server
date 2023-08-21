reload(){
	g++ main.cpp -o ./dist/main	
}
while true; do 
	inotifywait -e modify .
	reload
done
