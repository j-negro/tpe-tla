package classes;

import java.util.ArrayList;
import java.util.List;

public class MelodyWrapper {
    private final List<Melody> melodies;

    public MelodyWrapper() {
        this.melodies = new ArrayList<>();
        this.melodies.add(new Melody());
    }

    public MelodyWrapper setBpm(int bpm) {
        for (Melody melody : this.melodies)
            melody.setBpm(bpm);
        return this;
    }

    public int getBpm() {
        return this.melodies.get(0).getBpm();
    }

    public MelodyWrapper setBpm(boolean bpm) {
        for (Melody melody : this.melodies)
            melody.setBpm(bpm ? 120 : 60); // TRUE = 120, FALSE = 60 in this language
        return this;
    }

    public MelodyWrapper addNote(MelodyWrapper melodyWrapper) {
        this.melodies.addAll(melodyWrapper.melodies);
        return this;
    }

    public MelodyWrapper addNote(Melody melody) {
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

    public MelodyWrapper removeNote(int index) {
        int i = index;
        for (Melody melody: this.melodies) {
            if (i < melody.getSize()) {
                melody.removeNote(i);
                return this;
            }
            i -= melody.getSize();
        }

        return this;
    }

    public MelodyWrapper addNote(Note note, int index) {
        Melody toAdd = null;
        int noteCounter = 0;
        for (Melody melody: melodies) {
            if (noteCounter >= index) {
                toAdd = melody;
                break;
            }
            noteCounter += melody.getSize();
        }
        if (toAdd != null)
            toAdd.addNote(note, noteCounter - index);
        return this;
    }

    public MelodyWrapper addNote(MelodyWrapper melodyWrapper, int index) {
        int melodyIndex;
        int noteCounter = 0;
        boolean found = false;
        for (melodyIndex = 0; melodyIndex < this.melodies.size() && !found; melodyIndex++) {
            Melody melody = this.melodies.get(melodyIndex);
            noteCounter += melody.getSize();
            if (noteCounter >= index) {
                found = true;
            }
        }
        if (index > noteCounter)
            return this;
        melodyIndex--;
        Melody melody = this.melodies.get(melodyIndex);
        Melody secondHalf = melody.split(noteCounter - index);
        int j;
        for (j = 0; j < melodyWrapper.melodies.size(); j++) {
            this.melodies.add(melodyIndex + j + 1, melodyWrapper.melodies.get(j));
        }
        this.melodies.add(melodyIndex + j + 1, secondHalf);
        return this;
    }

    public int getDuration() {
        int duration = 0;
        for (Melody melody : this.melodies)
            duration += melody.getDuration();
        return duration;
    }

    public void raiseTone() {
        for (Melody melody : this.melodies)
            melody.raiseTone();
    }

    public void lowerTone() {
        for (Melody melody : this.melodies)
            melody.lowerTone();
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (Melody melody : this.melodies)
            sb.append(melody.toString()).append(" ");
        return sb.toString();
    }
}
