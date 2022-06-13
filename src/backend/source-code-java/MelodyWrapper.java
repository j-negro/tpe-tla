import java.util.ArrayList;
import java.util.List;

public class MelodyWrapper {

    private int bpm;
    private List<Note> notes;

    public MelodyWrapper() {
        this.bpm = 120;
        this.notes = new ArrayList<>();
    }

    public MelodyWrapper setBpm(int bpm) {
        this.bpm = bpm;
        return this;
    }

    public int getDuration() {
        double duration = 0;
        for (Note note : this.notes)
            duration += note.getDuration().getDuration() * ((double) this.bpm) / 60;
        return (int) Math.ceil(duration);
    }

    public MelodyWrapper addNote(Note note) {
        this.notes.add(note);
        return this;
    }

    public MelodyWrapper removeNote(Note note) {
        this.notes.remove(note);
        return this;
    }
}
