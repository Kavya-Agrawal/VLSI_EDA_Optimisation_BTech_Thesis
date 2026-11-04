// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.08116601;
  double density_weight = 0.57449663;
  double prefix_weight = 0.37724225;
  double neighborhood_weight = 0.30051286;
  double late_weight = 0.27334757;
  double critical_weight = 0.04219401;
  unsigned budget = 12;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
