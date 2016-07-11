package lab0325;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;

public class P176 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		BufferedReader in;
		FileWriter out;
		
		String testCase;
		String temp;
		int testNum;
		String password;
		
		String path = P176.class.getResource("").getPath();
		try {
			in = new BufferedReader(new FileReader(path+"input_P176.txt"));
			out = new FileWriter("output_P176.txt");
			
			testNum = Integer.valueOf(in.readLine());
			password = in.readLine();
			char st = password.charAt(0);
			boolean state = false;
			
			// password is String value ex "7536"
			for(int k = 0; k < testNum; k++){
				
				System.out.println("#"+k +" ");
				
				testCase = in.readLine();
				
				for(int i = 0; i < testCase.length(); i++){
					
					if(testCase.charAt(i) == st){
						temp = testCase.substring(i, i+3);
						
						if( temp.equals(password) ){
							System.out.println("1");
							state = true;
							break;
						}
					}
					
				}
				if(state == false){
					System.out.println("0");
				}
				
				
			}
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
