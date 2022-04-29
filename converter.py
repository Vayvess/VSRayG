with open("songs/in.qua", "r") as f:
    with open("songs/out.vsrg", "wb+") as g:
        while not f.readline().startswith("HitObjects:"):
            pass

        while True:
            line = f.readline()
            if "StartTime" in line:
                timing = int(line.split(" ")[-1].strip("\n"))
                g.write(timing.to_bytes(4, "little"))
                lane = int(f.readline().split(" ")[-1].strip("\n"))
                g.write(lane.to_bytes(4, "little"))
            elif line == "":
                break
