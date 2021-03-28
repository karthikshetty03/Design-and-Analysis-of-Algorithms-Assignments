
# Contributing

Thank you for considering and taking the time to contribute! 

The following are guidelines for contributing to this project.

## How to Report Bugs

Please open [a new issue in the appropriate GitHub repository][new-issue] with steps to reproduce the problem you're experiencing.

Be sure to include as much information including screenshots, text output, and both your expected and actual results.

## How to Request Enhancements

Firstly please refer to the applicable [github-repo] and search in the [issues-list] to make sure that your idea has not been (or is not still) considered.

If it is not yet considered or something more can be added then please create a new issue in the GitHub repository[new-issue] describing your enhancement.

Be sure to include as much detail as possible including step-by-step descriptions, specific examples, screenshots or mockups, and reasoning for why the enhancement might be worthwhile.

## 📌 Setting up Locale Environment

### 🚩 Forking repository :

1. Firstly you have to make your own copy of project. For that you have to fork the repository. You can find the fork button on the top-right side of the browser window. (Refer image below )
2. Kindly wait till it gets forked.
3. After that copy will look like `<your-user-name>/Design-and-Analysis-of-Algorithms-Assignments` forked from `karthikshetty03/DAA-Assignments`.
   <img src="./doc/images/fork.png" alt="Demo fork image" align="center"/>

### 🚩 Clone repository :

1. Now you have your own copy of project. Here you have to start your work.
2. Go to desired location on your computer where you want to set-up the project.
3. Right click there and click on `git bash`. A terminal window will pop up
4. Type the command `git clone <your-fork-url>.git` and hit enter.(Refer the image to copy url)
5. Wait for few seconds till the project gets copied
   <img src="./doc/images/copy.png" alt="Demo copy image" align="center"/>

### 🚩 Setting up remote :

1. Now you have to set up remote repositories
2. Type `git remote -v` in terminal to list remote connections to your repo.
3. It will show something like this:

```console

origin  https://github.com/<your-user-name>/Design-and-Analysis-of-Algorithms-Assignments (fetch)
origin  https://github.com/<your-user-name>/Design-and-Analysis-of-Algorithms-Assignments (push)

```

4. Now type the command `git remote add upstream https://github.com/karthikshetty03/Design-and-Analysis-of-Algorithms-Assignments` this will set upstream as main directory
5. Again type in command `git remote -v` to check if remote has been set up correctly
6. It should show something like this :

```console

origin  https://github.com/<your-user-name>/Design-and-Analysis-of-Algorithms-Assignments (fetch)
origin  https://github.com/<your-user-name>/Design-and-Analysis-of-Algorithms-Assignments (push)
upstream        https://github.com/karthikshetty03/Design-and-Analysis-of-Algorithms-Assignments (fetch)
upstream        https://github.com/karthikshetty03/Design-and-Analysis-of-Algorithms-Assignments (push)

```

### 🚩 Creating a branch :

Whenever you want to contribute to any project. It is best practice that you should create a branch and push the branch as PR rather than directly pushing main/master branch

1. `git branch` will list all the branches in the repository
2. Now type `git branch <your-branch-name>` to create your branch
3. You can check the created branch by `git branch`
4. But still if you start editing the edits will go to the main branch. To change the path , type in `git checkout <your-branch-name>`
5. Now you are ready to do the desired changes.

By this time you can see a message on your github fork as `your fork is ahead of codeforcause:master by <number> of commits` and you can also see a button `Compare and pull request`.

1. Click on `Compare and pull request` 
2. Describe the changes and Click on `Pull request`
