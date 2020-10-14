for f  in *-micro.cfg; do
  awk '{if(NR==16){print "maxsize=4"}else{print}}' "$f" > fifo && mv fifo "$f";
done
