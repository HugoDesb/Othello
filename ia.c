int fonction minimax (int depth)
{
   if (depth == 0)
      return nombre de cases prises;
    
   int bestScore;
   move bestMove;

   if (nœud == MAX) { //=Programme
      bestScore = -INFINITY;
      for (each possible move m/* chaque coup de coup-jouable*/) {
       	//nouveau othellier 
         int score = minimax (depth - 1)
      	//free othellier
         if (score > bestScore) {
            bestScore = score;
            bestMove = m ;
         }
      }
   }
   else { //type MIN = adversaire
      bestScore = +INFINITY;
      for (each possible move m/* chaque coup de coup-jouable*/) {
      	//nouveau othellier 
         int score = minimax (depth - 1)
        //free othellier
         if (score < bestScore) {
            bestScore = score;
            bestMove = m ;
         }
      }
   }
   return bestscore ;
}
