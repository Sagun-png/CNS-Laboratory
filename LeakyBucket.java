import java.util.*;

public class LB {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter number of time intervals");
		int n = sc.nextInt();
		int t[] = new int[n];
		System.out.println("Enter time intervals");
		for(int i=0; i<n; i++)
			t[i] = sc.nextInt();
		int lct = t[0];
		System.out.println("Enter value of l and i");
		int l = sc.nextInt();
		int i = sc.nextInt();
		int x=0, x_dash=0;
		for(int j=0; j<n;j++) {
			x_dash=x-(t[j]-lct);
			if(x_dash>l)
			{
				System.out.println("The packet is non-conforming "+t[j]);			
		    }
			else
			{
				x=x_dash+i;
				lct=t[j];
				System.out.println("The packet is confirming "+t[j]);
			}
		}
		sc.close();
	}
}
