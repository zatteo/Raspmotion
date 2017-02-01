import com.leapmotion.leap.Controller;
import com.leapmotion.leap.Listener;

public class SampleListener extends Listener{
	    public void onConnect(Controller controller) {
	        System.out.println("Connected");
	    }

	    public void onFrame(Controller controller) {
	        System.out.println("Frame available");
	    }
}
