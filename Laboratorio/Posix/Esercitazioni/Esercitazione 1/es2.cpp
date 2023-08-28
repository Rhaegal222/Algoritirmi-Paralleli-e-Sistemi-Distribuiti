void* run(void* arg){
    int* p = (int*)arg;
    sleep(1);
    sleep(4-(*p));
}

int main(int argc, char* argv[]){
    pthread_t thid;
    int i = 1;
    pthread_create(&thid, NULL, &run, &i);
    sleep(1);
    i++;
    sleep(i);
    pthread_join(thid, NULL);
    return 0;
}