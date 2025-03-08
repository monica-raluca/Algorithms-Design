### Birladeanu Raluca-Monica 325CA - First PA Homework

# First problem - Servers

- The implementation of this problem can be found in `servere.cpp`, and the solution is written in the class `Servers`.
- The additional functions used are: `individualPower`, which uses the formula given to compute the individual power of a server based on a given value, and `minimumPower`, which computes the power of the cluster, which is basically the minimum individualPower of all our servers.
- These two functions are then used in order to find the maximum minimum power we could possibly obtain. 
- At first glance, this seemed to me like a binary search problem, which is what I first tried doing, attempting to go towards the maximum value possible, up until I achieved a certain precision. However, this didn't seem to work, since the algorithm was visibly flawed, not going in the right direction for the first step. 
- After noticing this, I tried the same binary search, only with a different approach. Instead of initializing an incipient value that I would then update during my search, I tried compiling two mid values, one having a very small offset in order to better determine in which part my algorithm should go. While this did work much better, it wouldn't work for bigger positive values or for negative ones. 
- All this time, the absolute value in my individualPower function has been bothering me, since that made the function not strictly monotonous, which was hindering my binary search approach. Hence, when I looked up ternary search, things clicked for me, since that is used for finding the maximum of a unimodal function, which was exactly what I was trying to achieve.
- From the point, the solution became obvious. I picked left and right to be the minimum and maximum values and performed the search until my precision threshold was reached (in this case 1e-6). I just split the array into three equal parts, evaluated the minimumPower using mid1 and mid2 as my respective values, and by comparing the obtained power, decided the direction in which I had to go. Lastly, I just returned the minimumPower using left as my desired value, which guaranteed that my final result will be the maximum possible one.

Complexity: The ternary search algorithm has a O(2 * log3n) complexity, while the minimumPower function calculates that in O(n) complexity, since it has to iterate through all the vector, so the total complexity will end up being O(4n * log3n).

# Second problem - Coloring
- The implementation of this problem can be found in `colorare.cpp`, and the solution is written in the class `Color`.
- For this problem, I implemented a `power` function which computes the fast power and also does the modulo in order to avoid any overflow issues.
- The solution to this problem was fairly more straight-forward after I drew some rectangles on a piece of paper in order to properly grasp the formulas.
- We can see that an initial vertical square has 3 possibilities, since we can color it in with each color at our disposal. An initial horizontal one, however, can take 6 coloring possibilities, since we have to stack two horizontal ones: the first one can take 3 colors, and the second any of the remaining 2, in order to ensure no same color is in an adjacent place.
- After we set our initial values, we can iterate through the rest of our pictures and compile our result. 
- If we have a vertical rectangle followed by either an horizontal or vertical one, we will multiply our result by two.
- If we have an horizontal rectangle followed by another horizontal one, we will multiply our result by three.
- If we have an horizontal rectangle followed by a vertical one, we will just multiply our result by one. Although this makes no difference to our final result, I decided to explicitly do this multiplication as well so I can better visualize the steps.

Complexity: Following the above rules, we can just do one liniar pass through our input and compile the result, checking our previous rectangle and our current one. The result is compiled while we read our input data in O(n) and the implemented `power` function has a O(log n) complexity, which makes our final complexity O(n log n).

# Third problem - Compression
- The implementation of this problem can be found in `compresie.cpp`, and the solution is written in the class `Compress`.
- For this problem, I used two vectors which I first filled with my input in the `read_input` function.
- The approach for this problem was to basically simulate the compression using a liniar pass-through. At first, I initialized two sums, one for each vector, which was exactly the first element of each vector. While passing through both vectors until one of them ended, I compared the sums and handled three different cases:
    - In case of sum equality, I increase the result and advance in both vectors, resetting the sum to the element I ended up on.
    - In case of inequality, I would advance only in the vector with the smaller sum, increasing it, trying to achieve an equal sum as the one in my other vector.
- After one of my vectors ended, I went through the vector that was not yet over, adding up all remaining elements:
    - If my sum with all remaining elements is now equal to the sum in the other vector, I once again increase the result, since this means our sequence length extended.
    - Otherwise, I return -1, since this means we could not compress the vectors in order for them to end up the same.

Complexity: Since I just pass through the vectors and compile the sums, performing all the required checks in that pass, and then go through the remaining elements, the complexity boils down to a linear one, O(n + m).

# Fourth problem - Encrypted
- The implementation of this problem can be found in `criptat.cpp`, and the solution is written in the class `Encryption`.
- For this problem, I implemented a few additional functions, such as `get_letters`, which returns a set with all the characters I have at my disposal in order to form a password. I used a set in order to ensure that only unique letters will be added, without having to manually perform some checks. The other functions are `merge` and `mergeSort`, which are inspired by the implementation on geeksforgeeks. The merge sort is used in order to sort first by the relative frequency of the dominant letter, then by the length of the word.
- In terms of data structures, this is where I started to have a bit of fun, since I realized I had the whole STL at my disposal. I first struggled with some vector of pairs but scrapped that idea (after quite a bit more time than I should've). I used a set in which I stored all my distinct letters and a map in which I associated a index to each letter, so that I wouldn't have to iterate through 26 letters of the English alphabet and check if they exist in my word.
- I then used a frequency matrix in which I stored the appearences of each letter in each word.
- The solution for this problem uses a greedy approach which iterates through all the distinct letters, assuming that letter as dominant at that given step. After sorting by the dominant letter, we are ready to proceed with the greedy algorithm. I go through all my words and only add the current word if my resulting password will respect the condition for the dominant letter. After I finish forming my password, I check if my current max length is smaller than the length of the newly obtained password. If it is, I update it and move on to the next letter, returning the max length after passing through all the letters.

Complexity: Since we iterate through the unique letters (which is a constant that is at most 8), and we do an initial merge sort in O(n log n) before then going through all our words in O(n), our final complexity will end up being O(n log n).

# Fifth problem - Offer
- The implementation of this problem can be found in `oferta.cpp`, and the solution is written in the class `Offer`.
- For the simpler version of the problem, I decided to use a dynamic programming approach with a vector, in which at each step dp[i] I would save my minimum sum up until that point. The initial cases dp[1] and dp[2] are straigh-forward, since I can only have one minimum sum with only one element, and in the cases of two prices, my best sum would be obtained by taking the half price offer.
- After that, for each subsequent price, I will check the minimum sum that I could obtain from all three offers I could take: the half price offer, the full price one, or the free offer. In the end, my dp[n] will contain the smallest possible sum I could obtain.
- For the version where k is different from 1, I decided to use a matrix dp[i][j], where that element represents the (j + 1)-th smallest sum formed with the first i prices. In the end, the k-th smallest sum will be in dp[n][k - 1].
- If I only have one price, I check what k smallest sum I have to output: if k is also 1, then I just return my given price, since there is no better offer, and if k is anything bigger than my number of prices, then I just output -1, since I don't have that many possible offers.
- After doing these additional checks, I first fill in the dp matrix for the first and second prices, after which I compute all the possible offers that I can obtain with the previous sums in my dp matrix, offers which I store in the vectors halfPrice, freePrice and fullPrice, only if my respective dp is different from -1 (if it has a usable value).
- After filling in my vectors, I first merge all of them into the sortedPrices vector in order to have the values in ascending order, and then remove all the duplicates. 
- Finally, I insert only the first k sums in the matrix of sums. If the vector has less than k values stored, then I only insert those.

Complexity: I go through the prices in a liniar manner, while then going through k iterations in order to fill in my vectors, which leads to a O(n * k) complexity. The merge for partial prices is done in O(halfPrice.size() + fullPrice.size()), while the final merge is done in O(partialPrices.size() + fullPrice.size()). Removing the duplicates from the final array is done in O(n) time. Taking all of these into account, the final complexity is around O(max((n * k), (n^2))).


