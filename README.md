# cybersecurity [![Build Status](https://travis-ci.org/tigerjpg/cybersecurity.svg?branch=master)](https://travis-ci.org/tigerjpg/cybersecurity) [![Stories in Ready](https://badge.waffle.io/tigerjpg/cybersecurity.svg?label=ready&title=Ready)](http://waffle.io/tigerjpg/cybersecurity)

[![Throughput Graph](https://graphs.waffle.io/tigerjpg/cybersecurity/throughput.svg)](https://waffle.io/tigerjpg/cybersecurity/metrics) 

#Rules
1. Never work on ``master``
2. Pulling ``master`` should never create a merge commit
3. Work on _Issue Specific Feature Branches_
4. Regularly ``git rebase origin/master`` _Feature Branches_ to updated ``master``
5. Always rebase before you push
5. _Peer Review Pull Request_
6. _Delete Feature Branch_ after _Pull Request Approval_

#Workflow
[Checkout this interactive guide](https://guides.github.com/introduction/flow/) to get an idea of the workflow, nevermind the details.

##Identify the Feature
Identify the feature that you want to begin working on here:  [![Stories in Ready](https://badge.waffle.io/FourMen/bulk-club.png?label=ready&title=Ready)](https://waffle.io/FourMen/bulk-club)

Ideally, you should take the highest priority feature assigned to you. But feel free to assign yourself an unassigned feature. Alternatively, you can refer to _GitHub Issues_.

##Pull master updates
Pull the latest updates on your local repo, make sure you keep ``master`` current.
```
git checkout master
git pull origin master
```

##Create a Feature Branch
Make sure you are on master, we want to branch from a stable state.
```
git checkout master
```
Create a _Feature Branch_ with a well formated branch name:
* The issue number
* A hyphonated lower case human readable short feature name
```
git checkout -b 17-short-feature-name
```
Push it to the remote, so we know you're working on it
```
git push origin 17-short-feature-name
```

##Work on the Feature Branch
Write your code and commit often (anytime you change something or write something significant)
```
git add -A
git commit -m 'Useful commit message'
```

##Keep Feature Branch up-to-date with master
As you work periodically, after you know of changes to master or when your feature is complete -
Fetch the remote master and rebase your _Feature Branch_ to those changes: 
```
git fetch origin master
git rebase origin/master
```

##Push Your Feature Branch
``` git push origin 17-short-feature-name```

##Create a Pull Request
On GitHub, navigate to your feature branch and create a Pull Request to the ``testing`` branch.

[See this guide for more detailed instructions](http://yangsu.github.io/pull-request-tutorial)

##Peer Review Pull Request
Review code and suggest fixes, each member must approve the code before approving.
* Fixes would be made locally on the feature branch and then the updates pushed with
``` 
git push origin 17-short-feature-name
```
* This will automatically update the pull request

##Approve Pull Request
After each team member has approved your feature the scrum lord will pull your code to the ```testing``` branch for integration testing. As better tests are developed, this process will be streamlined, but for now we will have one person incharge of integrating changes.

##Close The Issue
When making your final commit, include the _closes_ keyword in the end of the message.
```
git commit -m "... closes #17
```
The issue should be automatically linked by the commit comment, close the issue

##Delete Feature Branch (Optional)
You can do this immediately to keep the repo tidy, but you may also choose to wait until later
* Locally - Using ``git branch -d 17-short-feature-name``
* On GitHub - Using the option on the _Pull Request_


#Style Guide

For this project, we will be using the [Google style guide for C++](https://google-styleguide.googlecode.com/svn/trunk/cppguide.html).

###A Brief Doxygen Style Guide

**In QT, typing </*!> + enter above a declaration will produce a doxygen comment block.**

Full commenting manual can be found [here](http://www.stack.nl/~dimitri/doxygen/manual/docblocks.html).

#### Things to note about Doxygen comments
* Comments can come before the code item.
* For class members and parameters they may also come after them.
* They may be either brief (one line) or detailed or both.
* Put the reference documentation type comments (class and method descriptions) **in the .h file** and *not* in (or, at least, in addition to) the .cpp files. 

#### Brief comment before
Add an extra "/"


```
/// This method does something
void DoSomething();
```


#### Detailed comment before
Add an extra "*"


```
/** This is a method that does so
  * much that I must write an epic 
  * novel just to describe how much
  * it truly does. */
void DoNothing();
```


- the intermediate leading "*"s are optional.

#### Brief comment after
Add an extra "/<"


```
void DoSomething(); ///< This method does something
```


### Detailed comment after
Add an extra "*<"


```
void DoNothing(); /**< This is a method that does so
  * much that I must write an epic 
  * novel just to describe how much
  * it truly does. */
```


- the intermediate leading "*"s are optional.

#### Example .h file
Below is a full example.


```
/**
 * \class ExampleClass
 *
 * \brief Provide an example
 *
 * This class is meant as an example.  It is not useful by itself
 * rather its usefulness is only a function of how much it helps
 * the reader.  It is in a sense defined by the person who reads it
 * and otherwise does not exist in any real form. 
 *
 * \note Attempts at zen rarely work.
 *
 * \author (last to touch it) $Author: bv $
 *
 * \version $Revision: 1.5 $
 *
 * \date $Date: 2005/04/14 14:16:20 $
 *
 * Contact: bv@bnl.gov
 *
 * Created on: Wed Apr 13 18:39:37 2005
 *
 * $Id: doxygen-howto.html,v 1.5 2005/04/14 14:16:20 bv Exp $
 *
 */

#ifndef EXAMPLECLASS_H
#define EXAMPLECLASS_H

class ExampleClass
{

public:

    /// Create an ExampleClass
    ExampleClass();

    /// Create an ExampleClass with lot's of intial values
    ExampleClass(int a, float b);

    ~ExampleClass();

    /// This method does something
    void DoSomething();

    /** This is a method that does so
      * much that I must write an epic 
      * novel just to describe how much
      * it truly does. */
    void DoNothing();

    /** \brief A useful method.
      * \param level an integer setting how useful to be
      * \return Output that is extra useful
      * 
      * This method does unbelievably useful things.  
      * And returns exceptionally useful results.
      * Use it everyday with good health.
      */
    void* VeryUsefulMethod(bool level);

private:

    const char* fQuestion; ///< the question
    int fAnswer;           ///< the answer 

};                              // end of class ExampleClass

#endif  // EXAMPLECLASS_H
```
