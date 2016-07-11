package lab0325;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.reflect.Array;
import java.util.Arrays;

public class P162 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		
		BufferedReader in;
		FileWriter out;
		
		int testNum;
		String[] t = new String[6];
		String temp;
		
		String path = P162.class.getResource("").getPath();
		try {
			in = new BufferedReader(new FileReader(path + "input_P162.txt"));
			out = new FileWriter("output.txt");
			
			testNum = Integer.valueOf(in.readLine());
			for(int k = 0; k < testNum; k++){
				
				temp = in.readLine();
				
				
				t = temp.split(" ");
				
				
				// 0,1 2,3 4,5
				
				triangle tr = new triangle();
				
				tr.p1.x = Integer.valueOf( t[0] );
				tr.p1.y = Integer.valueOf( t[1] );
				tr.p2.x = Integer.valueOf( t[2] );
				tr.p2.y = Integer.valueOf( t[3] );
				tr.p3.x = Integer.valueOf( t[4] );
				tr.p3.y = Integer.valueOf( t[5] );
				
				if( tr.isPoint()  ){
					System.out.println("def 0");
					continue;
				}
				
				System.out.println("def " +tr.isRight(tr.p1,tr.p2,tr.p3));
				
				
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

}

class Pos{
	int x;
	int y;
}

class triangle{
	Pos p1,p2,p3;
	
	triangle(){
	p1 = new Pos();
	p2 = new Pos();
	p3 = new Pos();
	};
	
	boolean isPoint(){
	
		if( (p1.x == p2.x && p1.x == p3.x) || (p1.y == p2.y && p1.y == p3.y) )
			return true;
		
		Pos ex = new Pos();
		ex.x = p2.x;
		ex.y = p1.y;
		
		Pos ex1 = new Pos();
		ex1.x = p2.x;
		ex1.y = p3.y;
		
		int a = 0;
		a += isRight( p2,p1,ex );
		a += isRight( p2,p3,ex1 );
		
		
		return a==2;
		// right가 아니다. true..
	}
	
	int isRight(Pos p1,Pos p2, Pos p3){
		
		double side_A = length(p1,p2);
		double side_B = length(p3,p2);
		double side_C = length(p1,p3);
		

		
		// 가장 큰 변 찾는 방법?
		
		double large;
		double result;
		int def;
		
		large = (side_A >= side_B)? side_A : side_B;
		large = (large >= side_C)? large : side_C;
		
		if( large == side_A ){
			
			result = (side_B * side_B) + (side_C * side_C) - (large*large);
			
		} else if(large == side_B ){
			result = (side_A * side_A) + (side_C * side_C) - (large*large);
		} else 
			result = (side_B * side_B) + (side_A * side_A) - (large*large);
		
		
		def = (result > 0)? 3 : 2;
		if( (int)result == 0 )
			def = 1;
		
		return def;
	}
	
	double length(Pos A, Pos B){
		
		int diff_x,diff_y;
		
		diff_x = Math.abs(A.x - B.x);
		diff_y = Math.abs(A.y - B.y);
		
		return Math.sqrt( (diff_x * diff_x) + (diff_y * diff_y) );
		
	}
}