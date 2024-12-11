inline rotate(){
  int copy[16];
  i = 0;
  temp = 12;
  do
    ::(i < 16) -> 
    copy[i] = solution[temp];
    temp = (temp + 13) % 17;
    i++;
    ::else->break
  od
  i = 0;
  do
    ::(i < 16) -> solution[i]= copy[i]; i++;
    ::else->break
  od
}

inline sudokuprint(){
  i = 0;
  do
    ::(i < 16) -> printf("%d ", solution[i]);
    if
      ::(i % 4 == 3) -> printf("\n");
      ::else
    fi
    i++;
    ::else->break;
  od
  printf("\n");
}

inline move(){
  i = 0;
  do
    ::(i < 16) ->
    if
      ::(original[i] != 0) -> quantities[original[i] - 1]++;
      ::else
    fi
    solution[i] = original[i];
    i++;
    ::else->break
  od
}

inline try_shapes(){
  first_point = (letter % 2) + 4 * (letter > 1);
  i = 0;
  do
    ::(i < 4)->
    x = 7 - (i % 2) - 4 * (letter > 1);
    y = 13 - 4 * (i > 1) - (letter % 2);
    j = 0;
    last_point = 10 + 4 * (i > 1) + (i % 2);
    if
      ::(solution[first_point] != 0) -> a = solution[first_point];
      ::(solution[x] != 0) -> a = solution[x];
      ::(solution[y] != 0) -> a = solution[y];
      ::(solution[last_point] != 0) -> a = solution[last_point];
      ::else->j = 16;
    fi
    do
      ::(j < 16)->
      if
        ::(j!=x && j!=y && j!=last_point && j!=first_point && solution[j]==a) ->
        shapes[i + 4 * letter] = 1;
        break
        ::((j==x || j==y || j==last_point || j==first_point) && (solution[j] != 0) && (solution[j]!=a)) ->
        shapes[i + 4 * letter] = 1;
        break
        ::else
      fi
      j++;
      ::else->break
    od
    i++;
    ::else->break
  od
  write_shape()
}

inline write_shape(){
  // Check if we have only 1 possible shape for any letter
  letter = 0;
  do
    ::(letter < 4) ->
    temp = shapes[letter * 4] + shapes[letter * 4 + 1] + shapes[letter * 4 + 2] + shapes[letter * 4 + 3];
    if
      ::(temp == 4) ->goto fail; 
      ::(temp == 3) ->
    // we know there is only one possible shape
      i = 0;
      //find the shape
      do
        ::(!shapes[letter * 4 + i]) -> break;
        ::else -> i++;
      od

      first_point = (letter % 2) + 4 * (letter > 1);
      x = 7 - (i % 2) - 4 * (letter > 1);
      y = 13 - 4 * (i > 1) - (letter % 2);
      last_point = 10 + 4 * (i > 1) + (i % 2);
      if
        ::(solution[first_point] != 0)->
        temp = solution[first_point];
        solution[x] = temp;
        solution[y] = temp;
        solution[last_point] = temp;
        quantities[temp - 1] = 4;
        done[letter] = 1;
        ::(solution[x] != 0)->
        temp = solution[x];
        solution[first_point] = temp;
        solution[y] = temp;
        solution[last_point] = temp;
        quantities[temp - 1] = 4;
        done[letter] = 1;
        ::(solution[y] != 0)->
        temp = solution[y];
        solution[first_point] = temp;
        solution[x] = temp;
        solution[last_point] = temp;
        quantities[temp - 1] = 4;
        done[letter] = 1;
        ::(solution[last_point] != 0)->
        temp = solution[last_point];
        solution[first_point] = temp;
        solution[x] = temp;
        solution[y] = temp;
        quantities[temp - 1] = 4;
        done[letter] = 1;
        ::else ->
      // we don't know the number but we know the shape
        temp = done[0] + done[1] + done[2] + done[3];
        if
          ::(temp == 3)->
        // we know all other numbers, so the one missing is ours
          temp = 10 - (solution[0] + solution[1] + solution[4] + solution[5]);
          solution[first_point] = temp;
          solution[x] = temp;
          solution[y] = temp;
          solution[last_point] = temp;
          quantities[temp - 1] = 4;
          done[letter] = 1;
          ::(temp < 3) ->
          if
            ::(quantities[0] == 0) -> temp = 1;
            ::(quantities[1] == 0) -> temp = 2;
            ::(quantities[2] == 0) -> temp = 3;
            ::(quantities[3] == 0) -> temp = 4;
          fi
          solution[first_point] = temp;
          solution[x] = temp;
          solution[y] = temp;
          solution[last_point] = temp;
          quantities[temp - 1] = 4;
          done[letter] = 1;
          ::else -> goto end;
        fi
      fi
      ::else
    fi
    letter++;
    ::else -> break
  od
}

init{
  int original[16], quantities[4], solution[16];
  int i, j, k, temp;
// To change the cells. Read left to right, top to bottom 
  original[0] = 1;
  original[1] = 0;
  original[2] = 0;
  original[3] = 0;
  original[4] = 4;
  original[5] = 3;
  original[6] = 1;
  original[7] = 0;
  original[8] = 0;
  original[9] = 0;
  original[10] = 3;
  original[11] = 0;
  original[12] = 0;
  original[13] = 4;
  original[14] = 2;
  original[15] = 1;
  
// Start creating the solution
  //because there is no char a is represented by 1, b by 2...
  bool done[4];
  move()
  printf("input:\n");
  sudokuprint();

// Choose the best starting quadrant
  // Look for the most populated quadrant (clockwise)
  int amount[4];
  amount[0] = (original[0] != 0) + (original[1] != 0) + (original[4] != 0) + (original[5] != 0);      // top left
  amount[1] = (original[2] != 0) + (original[3] != 0) + (original[6] != 0) + (original[7] != 0);      // top right
  amount[2] = (original[10] != 0) + (original[11] != 0) + (original[14] != 0) + (original[15] != 0);  // bottom right
  amount[3] = (original[8] != 0) + (original[9] != 0) + (original[12] != 0) + (original[13] != 0);    // bottom left
  
  k = 1;
  int rotations = 0;
  do
    ::(k < 4) ->
    if 
      ::(amount[k] > amount[rotations]) -> rotations = k;
      ::else
    fi
    k++;
    ::else -> break
  od
  
  // rotate as many times as needed to put the best quadrant top left
  int r = 0;
  do
    ::(r < rotations) -> rotate(); r++;
    ::else -> break
  od

  
  // Check if any letter is complete
  bool shapes[16];
  int x, y, first_point, last_point, letter, a;
  k = 0;
  do
    ::(k < 4) ->
    if
      ::(quantities[k] > 4) -> goto fail;
      ::(quantities[k] == 4) -> letter = k; try_shapes();
      ::else
    fi
    k++;
    ::else -> break;
  od
  
// Try shapes
  k = 0;
  do
    ::(k < 16) -> letter = k % 4; try_shapes(); k++;
    ::else -> break
  od

  if
    ::(done[0] && done[1] && done[2] && done[3])
    ::else -> goto fail; 
  fi

end:
  do
    ::(r < 4) -> rotate(); r++;
    ::else -> break
  od
  printf("solution:\n");
  sudokuprint();
  if
    ::0 -> fail: printf("no (unique) solution found\n");
    ::else
  fi
}
