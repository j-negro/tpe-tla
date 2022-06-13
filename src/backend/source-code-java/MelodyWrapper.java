import java.util.ArrayList;
import java.util.List;

public class MelodyWrapper {
    private final List<Melody> melodies;

    public MelodyWrapper() {
        this.melodies = new ArrayList<>();
    }

    public MelodyWrapper addMelody(Melody melody) {
        this.melodies.add(melody);
        return this;
    }

    public MelodyWrapper removeMelody(Melody melody) {
        this.melodies.remove(melody);
        return this;
    }

    public MelodyWrapper addNote(Note note) {
        Melody last = this.melodies.get(this.melodies.size() - 1);
        last.addNote(note);
        return this;
    }

    public MelodyWrapper removeNote(Note note) {
        boolean removed = false;
        for (int i = 0; i < this.melodies.size() && !removed; i++) {
            removed = this.melodies.get(i).removeNote(note);
        }
        return this;
    }

    public int getDuration() {
        int duration = 0;
        for (Melody melody : this.melodies)
            duration += melody.getDuration();
        return duration;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (Melody melody : this.melodies)
            sb.append(melody.toString()).append(" ");
        return sb.toString();
    }
}
