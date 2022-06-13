import java.util.ArrayList;
import java.util.List;

public class Melody {

    private int bpm;
    private final List<Note> notes;

    public Melody() {
        this.bpm = 120;
        this.notes = new ArrayList<>();
    }

    public int getBpm() {
        return this.bpm;
    }

    public Melody setBpm(int bpm) {
        this.bpm = bpm;
        return this;
    }

    public void addNote(Note note) {
        this.notes.add(note);
    }

    public void addNote(Note note, int i) {
        this.notes.add(i, note);
    }

    public boolean removeNote(Note note) {
        return this.notes.remove(note);
    }

    public void removeNote(int index) {
        this.notes.remove(index);
    }

    public Melody split(int index) {
        Melody melody = new Melody();
        melody.setBpm(this.bpm);
        for (int i = index; i < this.notes.size(); i++) {
            melody.addNote(this.notes.get(i));
        }
        this.notes.removeAll(melody.notes);
        return melody;
    }

    public void raiseTone() {
        for (Note note : this.notes)
            note.raiseTone();
    }

    public void lowerTone() {
        for (Note note : this.notes)
            note.lowerTone();
    }

    public int getDuration() {
        double duration = 0;
        for (Note note : this.notes)
            duration += note.getRythm().getDuration() * ((double) this.bpm) / 60;
        return (int) Math.ceil(duration);
    }

    public int getSize() {
        return this.notes.size();
    }

    @Override
    public String toString() {
        if (this.bpm == 0)
            return "";
        StringBuilder sb = new StringBuilder();
        sb.append("T").append(this.bpm).append(" ");
        for (Note note : this.notes)
            sb.append(note.toString()).append(" ");
        return sb.toString();
    }
}
