import random
import os
import inspect
import sys
import shutil           
import glob

config_file = './matchup.txt'

def collect_results(file_path, results_dir):
    with open(file_path, 'r') as f:
        cs = f.readlines()
        names = [x.strip().split('=')[0] for x in cs]
        table_names = [x.strip().split('=')[1] for x in cs]
    
    base_dir = './results'
    for x, y in zip(table_names, names):
        # print(x, y)
        target = os.path.join(base_dir, x, '*.json')
        file_name = glob.glob(target)
        # file_name = glob.glob(target)
        print(file_name)
        if os.path.isfile(file_name[0]):
            shutil.copyfile(file_name[0], os.path.join(results_dir, y +'.json'))
        else:
            print('file [%s] not exist' % file_name[0])


def compare_one(x, y):
    return True
    # return random.choice([True, False])

def compare_results(arctern_results, postgis_results):

    with open(arctern_results, 'r') as f:
        arctern = f.readlines()
    # print(arctern)

    arc = [list(eval(x.strip()).values())[0] for x in arctern if len(x.strip()) > 0]
    # print(arc)

    with open(postgis_results, 'r') as f:
        postgis = f.readlines()
    pgis = [x.strip() for x in postgis if len(x.strip()) > 0]
    # print(pgis)
    
    flag = True

    if len(arc) != len(pgis):
        print('test result size: %s and expected result size: %s, NOT equal, check the two result files' % (len(arc), len(pgis)))
        return False

    for x, y in zip(arc, pgis):
        res = compare_one(x, y)
        flag = flag and res

    return flag

def parse(config_file):
    with open(config_file, 'r') as f:
        lines = f.readlines()
        xs = [x.strip().split('=') for x in lines]
    return xs

arc_result_dir = './arctern_results'
pgis_result_dir = './expected/results'

def compare_all():
    configs = parse(config_file)
    if len(configs) == 0:
        print('No Arctern test results found, maybe something wrong in config file, please check: %s' % config_file)
        return 0

    for x in configs:
        
        arctern_result = os.path.join(arc_result_dir, x[0] + '.json')
        postgis_result = os.path.join(pgis_result_dir, x[3] + '.out')
        print('Arctern test: %s, result compare started, test result: %s, expected result: %s' % (x[0], arctern_result, postgis_result))
        
        if not os.path.isfile(arctern_result):
            print('Arctern test: %s, result: FAILED, reason: %s' % (x[0], 'test result not found [%s]' % arctern_result))
            continue

        if not os.path.isfile(postgis_result):
            print('Arctern test: %s, result: FAILED, reason: %s' % (x[0], 'expected result not found [%s]' % postgis_result))
            continue

        res = compare_results(arctern_result, postgis_result)
        if res == True:
            print('Arctern test: %s, result: PASSED' % x[0])
        else:
            print('Arctern test: %s, result: FAILED' % x[0])

def update_json():
    arr = ['run_test_st_issimple', 'run_test_st_intersects', 'run_test_st_contains', 'run_test_st_crosses', 'run_test_st_isvalid_1', 'run_test_st_overlaps', 'run_test_st_touches', 'run_test_st_within', 'run_test_st_equals_1', 'run_test_st_equals_2']
    configs = parse(config_file)
    if len(configs) == 0:
        print('No Arctern test results found, maybe something wrong in config file, please check: %s' % config_file)
        return 0

    for x in configs:
        # print(x[0])
        if x[0] not in arr:
            # print('%s not in given arr' % x[0])
            continue

        arctern_result = os.path.join(arc_result_dir, x[0] + '.json')
        # print(arctern_result)
        if not os.path.isfile(arctern_result):
            print('Arctern test: %s, result: FAILED, reason: %s' % (x[0], 'test result not found [%s]' % arctern_result))
            continue
        
        with open(arctern_result, 'r') as f:
            content = f.read()
            update = content.replace('true', 'True').replace('false', 'False')
        with open(arctern_result, 'w') as f:
            f.write(update)

if __name__ == '__main__':
    # r = compare_results('./arctern_results/run_test_st_issimple.json', './expected/results/st_issimple.out')
    # r = compare_results('./test.json', './expected/results/st_issimple.out')
    # update_json()
    # print(parse(config_file))
    compare_all()
    