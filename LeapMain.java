/**
 * 
 */
import com.leapmotion.leap.*;
import java.io.IOException;
/**
 * @author Stery
 *
 */
public class LeapMain {
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		SampleListener listener = new SampleListener();
		Controller controller = new Controller();
		
		controller.addListener(listener);
		
		
        //Tant que entree n'est pas presse
        System.out.println("Press Enter to quit...");
        try {
            System.in.read();
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        //remove listener when done
        controller.removeListener(listener);

	}

}
