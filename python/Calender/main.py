import datetime


def print_meeting(meeting):
    """This function gets a meeting (as directory) and prints it
    :arg meeting the meeting to print"""
    print("*" * 20)
    print("Start time:", meeting["start_time"], "\nEnd time:", meeting["end_time"],
          "\nParticipant/s:", *meeting["participants"][:-1], "\nRoom:", meeting["room"])


def print_ad(ad_list):
    """This function gets a calendar and prints it
    :arg ad_list list of meetings to print"""
    for meeting in ad_list:
        print_meeting(meeting)
    print("*" * 20)


def print_ad_range(ad_list):
    """This function gets a calendar and prints it by range determine by the user
    :arg ad_list list of meetings to print"""
    date_start_str = input('Please enter a start date of the range in YYYY-MM-DD-HH-MM format: ')
    year_start, month_start, day_start, hour_start, minute_start = map(int, date_start_str.split('-'))
    start_time = datetime.datetime(year_start, month_start, day_start, hour_start, minute_start)
    date_end_str = input('Please enter an end date of the range in YYYY-MM-DD-HH-MM format: ')
    year_end, month_end, day_end, hour_end, minute_end = map(int, date_end_str.split('-'))
    end_time = datetime.datetime(year_end, month_end, day_end, hour_end, minute_end)
    if start_time > end_time:
        print('\033[93m'+"start time bigger then end time"+'\033[0m')
        return
    for meeting in ad_list:
        if meeting["start_time"] <= start_time and end_time >= meeting["start_time"]:
            print_meeting(meeting)
    print("*" * 20)


def is_correct_time(start_time, end_time):
    """This function checks if the time range is legal by these conditions:
    1. start time bigger than end time
    2. meeting starts and end on the same day
    3. meeting is between 09:00 to 18:00
    :arg start_time the meeting start time
    :arg end_time the meeting end time
    :returns True if it's correct or False if not"""
    if start_time > end_time:
        print('\033[93m'+"start time bigger then end time"+'\033[0m')
        return False
    if start_time.day is not end_time.day:
        print('\033[93m'+"meeting can only be made between 09:00 to 18:00 in the same day"+'\033[0m')
        return False
    if ((end_time - start_time).seconds/60) < 15:
        print('\033[93m'+"meeting must be more then 15 min"+'\033[0m')
        return False
    start_day = datetime.datetime(start_time.year, start_time.month, start_time.day, 9, 0)
    if start_day > start_time:
        print('\033[93m'+"meeting can only be made between 09:00 to 18:00 in the same day"+'\033[0m')
        return False
    end_day = datetime.datetime(start_time.year, start_time.month, start_time.day, 18, 0)
    if end_day < end_time:
        print('\033[93m' + "meeting can only be made between 09:00 to 18:00 in the same day" + '\033[0m')
        return False
    return True


def is_participant_available(start_time, end_time, par_time_list):
    """This function checks if participant/room is available for meeting
    :arg start_time the meeting start time
    :arg end_time the meeting end time
    :arg par_time_list the list of participant/room availability
    :returns True if it's available or False if not
    """
    for i in range(0, len(par_time_list), 2):
        if par_time_list[i] <= start_time <= par_time_list[i + 1]:
            print('\033[93m'+"Overlapping appointments, please reschedule"+'\033[0m')
            return False
        elif par_time_list[i] <= end_time <= par_time_list[i + 1]:
            print('\033[93m' + "Overlapping appointments, please reschedule" + '\033[0m')
            return False
        elif start_time <= par_time_list[i] <= end_time:
            print('\033[93m' + "Overlapping appointments, please reschedule" + '\033[0m')
            return False
        elif start_time <= par_time_list[i+1] <= end_time:
            print('\033[93m' + "Overlapping appointments, please reschedule" + '\033[0m')
            return False
    return True


def create_meeting(participants_list):
    """This function creates a meeting
    :arg participants_list List of existing participants
    :returns meeting or None if fail
    """
    date_start_str = input('Enter a start date in YYYY-MM-DD-HH-MM format: ')
    year_start, month_start, day_start, hour_start, minute_start = map(int, date_start_str.split('-'))
    start_time = datetime.datetime(year_start, month_start, day_start, hour_start, minute_start)
    date_end_str = input('Enter a end date in YYYY-MM-DD-HH-MM format: ')
    year_end, month_end, day_end, hour_end, minute_end = map(int, date_end_str.split('-'))
    end_time = datetime.datetime(year_end, month_end, day_end, hour_end, minute_end)
    if not is_correct_time(start_time, end_time):
        return None
    participants_str = input("Enter participants [Guy, Shir, Izik, Moshe] divided by '-' format: ")
    participants = participants_str.split('-')
    room_str = input("Enter a room number between 1-5: ")
    participants.append(room_str)
    for person in participants:
        if person in participants_list:
            if not is_participant_available(start_time, end_time, participants_list[person]):
                return
    for person in participants:
        if person in participants_list:
            participants_list[person].append(start_time)
            participants_list[person].append(end_time)
            participants_list[person].sort()
        else:
            participants_list[person] = [start_time, end_time]
    dict_meeting = {"start_time": start_time, "end_time": end_time,
                    "participants": participants, "room": room_str}
    print("Meeting created successfully")
    return dict_meeting


def find_meeting(ad_list):
    """This function finds and prints a meeting
    :arg ad_list List of existing meetings
    :returns meeting or None if fail
    """
    date_start_str = input('Please enter the start date of the meeting you seek in YYYY-MM-DD-HH-MM format: ')
    year_start, month_start, day_start, hour_start, minute_start = map(int, date_start_str.split('-'))
    start_time = datetime.datetime(year_start, month_start, day_start, hour_start, minute_start)
    room_str = input("Enter the room number of the meeting you seek between 1-5: ")
    for item in ad_list:
        if item["start_time"] == start_time and item["room"] == room_str:
            print_meeting(item)
            return item
    return None


def delete_meeting(ad_list, participants_list):
    """This function deletes a meeting
    :arg ad_list List of existing meetings
    :arg participants_list List of existing participants
    """
    print("To delete a meeting")
    meeting_to_delete = find_meeting(ad_list)
    if meeting_to_delete is None:
        print("meeting not found")
        return
    else:
        stat_time = meeting_to_delete["start_time"]
        participants = meeting_to_delete["participants"]
        for person in participants_list:
            if person in participants:
                for i in range(0, len(person)):
                    if participants_list[person][i] == stat_time:
                        participants_list[person].remove(participants_list[person][i+1])
                        participants_list[person].remove(participants_list[person][i])
                        break
        ad_list.remove(meeting_to_delete)
        print("Meeting has been deleted successfully")


def save_ad(ad_list):
    """This function saves the calendar to file
    :arg ad_list List of existing meetings
    """
    file_name = input("Please enter file name to save to:")
    file_in = open(file_name, 'w')
    for meeting in ad_list:
        print(meeting["start_time"], file=file_in)
        print(meeting["end_time"], file=file_in)
        print(*meeting["participants"], file=file_in)
        print(meeting["room"], file=file_in)
    print("Calender has been saved successfully")
    file_in.close()


def load_ad(ad_list, participants_list):
    """This function loads calendar form a file
    :arg ad_list List of existing meetings
    :arg participants_list List of existing participants
    """
    file_name = input("Please enter file name to load from:")
    file_in = open(file_name, 'r')
    if file_in is None:
        print("Fail to open file. Creating new calender")
        return
    i = 0
    for line in file_in:
        if i == 0:
            start_time = datetime.datetime.strptime(line[:-1], "%Y-%m-%d %H:%M:%S")
            i += 1
        elif i == 1:
            end_time = datetime.datetime.strptime(line[:-1], "%Y-%m-%d %H:%M:%S")
            i += 1
        elif i == 2:
            participants_str = line[:-1]
            participants = participants_str.split(' ')
            i += 1
        elif i == 3:
            room = line[:-1]
            i = 0
            for person in participants:
                if person in participants_list:
                    participants_list[person].append(start_time)
                    participants_list[person].append(end_time)
                    participants_list[person].sort()
                else:
                    participants_list[person] = [start_time, end_time]
            dict_meeting = {"start_time": start_time, "end_time": end_time,
                            "participants": participants, "room": room}
            ad_list.append(dict_meeting)
    print("Calender has been loaded successfully.")
    file_in.close()


def run_ad(ad_list, participants_list):
    """This function runs the calendar program
    :arg ad_list List of existing meetings
    :arg participants_list List of existing participants
    """
    choice = 0
    while 1 > choice  or choice > 2:
        print("Please enter one of the following options:")
        print("1. Load an existing calender.")
        print("2. Create a new calender.")
        choice = int(input("Your choice:"))
    if choice:
        load_ad(ad_list, participants_list)
    while True:
        print("Please enter one of the following options:")
        print("1. Create a meeting.")
        print("2. Delete a meeting.")
        print("3. Find and print a meeting.")
        print("4. Print all the meeting/s in a range.")
        print("5. Save calender.")
        print("6. Print all the meeting/s in the calender.")
        print("7. Close the program")
        choice = int(input("Your choice:"))
        if choice == 1:
            meeting1 = create_meeting(participants_list)
            if meeting1 is not None:
                ad_list.append(meeting1)
        elif choice == 2:
            delete_meeting(ad_list, participants_list)
        elif choice == 3:
            find_meeting(ad_list)
        elif choice == 4:
            print_ad_range(ad_list)
        elif choice == 5:
            save_ad(ad_list)
        elif choice == 6:
            print_ad(ad_list)
        elif choice == 7:
            print("Bye bye.")
            break
        else:
            print("Invalid choice, please try agine or press 7 to exit.")


def create_ad():
    """This function creates a calendar
    :returns calendar"""
    ad_list = []
    participants_list = {}
    return ad_list, participants_list


if __name__ == '__main__':
    # datetime.datetime(year,month, day, hour, minute, second)
    # 2022-12-01-09-30 2022-12-01-11-20 Guy-Shir-Izik
    # 2022-12-01-14-30 2022-12-01-15-20 Shir-Izik
    # 2022-12-02-14-30 2022-12-02-15-20 Guy-Izik
    # ad_save.txt
    my_ad, my_participants = create_ad()
    print("wellcome to Calendar")
    run_ad(my_ad, my_participants)
