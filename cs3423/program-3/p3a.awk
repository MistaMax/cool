{
    e = NF
    if(match($e,$1)){
        for(i = 2; i <= NF; i++){
            printf "%s ", $i
        }
        printf "\n"
    }
    else{
        print $e" "$0
    }
}