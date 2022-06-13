import java.util.ArrayList;
import java.util.List;

public class Melody {

    private final List<MelodyWrapper> melodies;

    public Melody() {
        this.melodies = new ArrayList<>();
    }

    public Melody addMelody(MelodyWrapper melody) {
        this.melodies.add(melody);
        return this;
    }

    public Melody removeMelody(MelodyWrapper melody) {
        this.melodies.remove(melody);
        return this;
    }

    public int getDuration() {
        int duration = 0;
        for (MelodyWrapper melody : this.melodies)
            duration += melody.getDuration();
        return duration;
    }
}
