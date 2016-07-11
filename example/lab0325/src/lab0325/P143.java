package lab0325;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class P143 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		
		BufferedReader in;
		FileWriter out;
		
		int i,j,k,m;
		String value;
		
		String path = P143.class.getResource("").getPath();
		try {
			in = new BufferedReader(new FileReader(path+"input_P143.txt"));
			out = new FileWriter("output_P143.txt");
		
			int testNum;
			testNum = Integer.valueOf(in.readLine());

			String inputStr;
			int strLen;
			char temp[]; // 임시 변수
			
			for(k=0; k<testNum; k++){
				
				int count = 0;
				inputStr = in.readLine();
				
				Palindrome pd = new Palindrome();
				
				System.out.println("#"+(k+1));
				System.out.println("입력받은 문자열 : "+inputStr);
				
				strLen = inputStr.length();
				out.write("#" + (k+1) + " ");
				
				// 0부터 크기까지 같을려면.. 0 10, 마지막요소가 0 1 2 3 4 5 6 7 8 9  9인데.??
				// = 없어도 될 거 같은데
				for( i =0; i <= strLen; i++){
					
					// 이녀석은 또 뭘까.. 
					for( j = 0; j<= strLen -i+1; j++){
						temp = new char[inputStr.length()-1];
						
						for(m = j; m < i+j; m++)
							temp[m] = inputStr.charAt(m);
						
						temp[m] ='\0';
						if(pd.check(temp,j)){
							char output[] = new char[k];
							
							for( m = 0; m < i; m++)
								output[m] = temp[j+m];
							
							System.out.print(output);
							System.out.println(" : 회문");
							
							out.write(output);
							out.write(" ");
							count++;
						}
					}
						
					
				}
				System.out.println("총 회문 개수 : "+count + "\n\n");
				
				// 이 부분 왜 있는거지?
				if(count == 0)
					out.write(count +"\r\n");
				else
					out.write(count +"\r\n");
						
				
				
			}
			in.close();
			out.close();
/*			// 1... 26 ..0 비웠음
			int[][] eachChar = new int[27][10];
			int[] eachCnt = new int[27];
			
			
			for(k =0; k< 1; k++ ){
				
				value = in.readLine();
				int idx = 0;
				int alpha;
				for( i = 0; i < value.length(); i++){
					
					for(j =0; j < 10; j++){
						if(eachChar[value.charAt(i)-64][j] == 0){
							eachCnt[value.charAt(i)-64] = j;
							break;
						}
					}
					
					eachChar[value.charAt(i) - 64][j] = i+1;  
					// A라면 65, -64해야, 90 -65 +1 = 26
				}
				System.out.println(value);
				System.out.println(eachChar.length+"    ");
				
			
				for(i =0; i< eachChar.length;i++){
					System.out.print(eachChar[i][0] + " " );
				}
				
				for(i =0; i<eachChar.length; i++){
					// 배열을 돌며 0 이 아닌요소만.. 체크할 순없나.
					for(j =0; j<eachChar[i][eachCnt[i]];j++){
						
						if(eachChar[i][eachCnt[i]-1] == eachChar[i][eachCnt[i]] -2 ){
							System.out.println("3회문~");
						}

					}
					
				}
				
			}
*/			
			
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

}

class Palindrome{
	
	boolean check(char input[],int k){
		int pal = 0;
		int j = 0;
		int limit;
		
		for(int i =0; i< input.length; i++){
			if(input[i] != '\0')
				j++;
			
		}
		limit = j;
		for(int i =0; i<j; i++,j--){
			if(input[i+k] == input[j-1+k]) //좌우 대칭이 되면
				pal++;
		}
		if(pal == (limit+1)/2)
			return true;
		else
			return false;
	}
	
}
