import java.util.ArrayList;
import java.util.List;

public class Melody {

    private int bpm;
    private final List<Note> notes;

    public Melody() {
        this.bpm = 120;
        this.notes = new ArrayList<>();
    }

    public Melody setBpm(int bpm) {
        this.bpm = bpm;
        return this;
    }

    public void addNote(Note note) {
        this.notes.add(note);
    }

    public boolean removeNote(Note note) {
        return this.notes.remove(note);
    }

    public int getDuration() {
        double duration = 0;
        for (Note note : this.notes)
            duration += note.getRythm().getDuration() * ((double) this.bpm) / 60;
        return (int) Math.ceil(duration);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("T").append(this.bpm).append(" ");
        for (Note note : this.notes)
            sb.append(note.toString()).append(" ");
        return sb.toString();
    }
}
