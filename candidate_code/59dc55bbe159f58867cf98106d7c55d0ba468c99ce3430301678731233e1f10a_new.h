// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.09928103;
  double density_weight = 0.43501328;
  double prefix_weight = 0.39299329;
  double neighborhood_weight = 0.25590493;
  double late_weight = 0.03266610;
  double critical_weight = 0.00646192;
  unsigned budget = 18;
  unsigned neighborhood = 6;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
