const MARGIN = 10;
const WIDTH = 640;
const HEIGHT = 480;
const EXAMPLE_GRAPH = {
    "nodes": [
      {
        "id": 1,
        "name": "A"
      },
      {
        "id": 2,
        "name": "B"
      }
    ],
    "links": [
      {
        "source": 1,
        "target": 2,
        "cost": 1
      }
    ]
  }

// Sacado de: https://www.d3-graph-gallery.com/graph/network_basic.html

let loadGraph = graph => {
  var svg = d3.select("#graph")
  .append("svg")
  .attr("style", "outline: thin solid black")
  .attr("width", WIDTH )
  .attr("height", HEIGHT)
  .append("g")
  .attr("transform", `translate(${MARGIN}, ${MARGIN})`)

  var link = svg
  .selectAll("line")
  .data(graph.links)
  .enter()
  .append("line")
  .style("stroke", "#aaa")

  var node = svg
  .selectAll("g")
  .data(graph.nodes)
  .enter()
  .append("g")

  node.append("circle")
  .attr("r", 20)
  .style("fill", "#5dedf0")
  .style("stroke", "black")

  node.append("text")
  .text(function(d) { return d.name })
  .style("font-family", "sans-serif")

  var simulation = d3.forceSimulation(graph.nodes)
  .force("link", d3.forceLink()
      .id(function(d) { return d.id; })
      .links(graph.links)
  )
  .force("charge", d3.forceManyBody().strength(-2000))
  .force("center", d3.forceCenter((WIDTH - 2*MARGIN) / 2, (HEIGHT - 2*MARGIN) / 2))
  .on("end", ticked);

  function ticked() {
      link
      .attr("x1", function(d) { return d.source.x; })
      .attr("y1", function(d) { return d.source.y; })
      .attr("x2", function(d) { return d.target.x; })
      .attr("y2", function(d) { return d.target.y; });

      node.selectAll("circle")
      .attr("cx", function (d) { return d.x; })
      .attr("cy", function (d) { return d.y; });

      node.selectAll("text")
      .attr("x", function (d) { return d.x-6; })
      .attr("y", function (d) { return d.y+6; })
  }
}

let parseGraph = (text) => {
  let nodes = []
  let links = []
  let source, target, cost
  let rows = text.split("\n")
  rows.forEach(row => {
    let columns = row.split(" ")
    columns.slice(0,2).forEach(node_name => {if (!nodes.includes(node_name)) {nodes.push(node_name)}})
    source = nodes.indexOf(columns[0])
    target = nodes.indexOf(columns[1])
    cost = columns[2]
    links.push({"source": source, "target": target, "cost": cost})
  })
    nodesObj = nodes.map(node => ({"id": nodes.indexOf(node), "name": node}))
    return ({"nodes": nodesObj, "links": links})
}

let buttonClick = () => {
  let svg = d3.select("#graph")
  svg.selectAll("*").remove()
  let parsedGraph = parseGraph(document.getElementById("graphinput").value)
  loadGraph(parsedGraph)
}

loadGraph(EXAMPLE_GRAPH);